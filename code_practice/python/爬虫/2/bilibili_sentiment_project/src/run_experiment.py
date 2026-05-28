"""
一键实验脚本。
运行后输入学习区和生活区 BV 号，程序会自动完成：爬取弹幕 -> 训练模型 -> 预测分析 -> 生成结果和图表。
运行：python src/run_experiment.py
"""
import re
from collections import Counter
from datetime import datetime
from pathlib import Path

import pandas as pd

from crawler_bilibili import crawl
from make_sample_data import generate_sample_data
from train_analyze import ROOT, TRAIN_DATA_PATH, analyze

TARGET_TOTAL = 5000
TARGET_PER_PARTITION = 2500
TOTAL_ROUNDS = 4
REVIEW_ROUNDS = 3
MAX_REVIEW_QUESTIONS = 100


def extract_bvid(value: str) -> str:
    value = value.strip()
    match = re.search(r"BV[A-Za-z0-9]+", value)
    return match.group(0) if match else value


def ask_bvid(partition: str) -> str:
    while True:
        bvid = extract_bvid(input(f"请输入{partition}视频 BV 号或视频链接："))
        if bvid.startswith("BV") and len(bvid) >= 8:
            return bvid
        print("输入格式不太对，请输入类似 BV1BiDaB1EEN 的 BV 号，或直接粘贴 B 站视频链接。")


def safe_experiment_name(name: str) -> str:
    default_name = datetime.now().strftime("experiment_%Y%m%d_%H%M%S")
    name = name.strip() or default_name
    name = re.sub(r'[<>:"/\\|?*\s]+', "_", name).strip("._")
    return name or default_name


def write_summary(path: Path, experiment_name: str, videos, raw_path: Path, crawl_stats, summary) -> None:
    metrics = summary["metrics"]
    stat = summary["stat"]
    lines = [
        f"实验名称：{experiment_name}",
        f"实验时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
        "",
        "输入视频：",
    ]
    for item in videos:
        lines.append(f"- {item['partition']}：{item['bvid']}")
    lines.extend([
        "",
        f"原始弹幕：{raw_path}",
        f"采集总量：{crawl_stats['total']} / 目标 {TARGET_TOTAL}",
        f"学习区采集量：{crawl_stats['partition_counts'].get('学习区', 0)} / 目标 {TARGET_PER_PARTITION}",
        f"生活区采集量：{crawl_stats['partition_counts'].get('生活区', 0)} / 目标 {TARGET_PER_PARTITION}",
        f"训练数据：{summary['train_data_path']}",
        f"预测数据：{summary['predict_path']}",
        f"最优模型：{summary['best_model']}",
        f"历史人工反馈样本数：{summary.get('feedback_count', 0)}",
        f"中性种子样本数：{summary.get('neutral_seed_count', 0)}",
        f"本轮待人工复核样本数：{summary.get('review_count', 0)}",
        f"本轮复核抽样比例：{summary.get('review_ratio', 0):.0%}",
        "",
        "模型指标：",
        metrics.to_string(index=False),
        "",
        "分区情感统计：",
        stat.to_string(index=False),
        "",
        f"结果目录：{summary['result_dir']}",
        f"图表目录：{summary['fig_dir']}",
        f"待复核样本：{summary.get('review_path', '')}",
        f"自动分析摘要：{summary.get('analysis_summary_path', '')}",
        f"低置信样本：{summary.get('diagnostics', {}).get('low_confidence_samples', '')}",
        f"词典模型冲突样本：{summary.get('diagnostics', {}).get('conflict_samples', '')}",
        f"按视频统计：{summary.get('diagnostics', {}).get('video_sentiment_stats', '')}",
        f"与上一轮对比：{summary.get('iteration_comparison_path', '')}",
        "",
        "按情感分类导出的弹幕：",
    ])
    for label, file_path in summary.get("label_group_paths", {}).items():
        lines.append(f"- {label}：{file_path}")
    path.write_text("\n".join(lines), encoding="utf-8")


def ensure_train_data() -> None:
    if TRAIN_DATA_PATH.exists():
        return
    print(f"未找到训练样例数据：{TRAIN_DATA_PATH}")
    print("正在自动生成课堂演示用标注样例数据...")
    generate_sample_data(TRAIN_DATA_PATH)


def summarize_crawl(rows):
    counts = Counter(row["partition"] for row in rows)
    return {"total": len(rows), "partition_counts": dict(counts)}


def print_crawl_requirement_note(crawl_stats):
    print(f"采集总量：{crawl_stats['total']} / 作业目标 {TARGET_TOTAL}")
    for partition in ["学习区", "生活区"]:
        count = crawl_stats["partition_counts"].get(partition, 0)
        print(f"{partition}：{count} / 目标 {TARGET_PER_PARTITION}")
    if crawl_stats["total"] < TARGET_TOTAL:
        print("提示：当前两个 BV 的可获取弹幕不足 5000 条，程序会先按实际数据完成分析；如需严格满 5000 条，请换弹幕更多的视频。")


def print_round_outputs(summary, result_dir, fig_dir, is_final=False):
    title = "最终结果" if is_final else "本轮结果"
    print(f"\n{title}输出：")
    print(f"- 分析结果：{result_dir}")
    print(f"- 图表文件：{fig_dir}")
    print(f"- 自动分析摘要：{summary['analysis_summary_path']}")
    print(f"- 分区统计：{result_dir / 'partition_sentiment_stats.csv'}")
    print(f"- 正面弹幕：{result_dir / 'positive_comments.csv'}")
    print(f"- 负面弹幕：{result_dir / 'negative_comments.csv'}")
    print(f"- 中性弹幕：{result_dir / 'neutral_comments.csv'}")
    print(f"- 待人工复核：{summary['review_path']}（约 {summary['review_ratio']:.0%}，共 {summary['review_count']} 条）")
    print(f"- 分区情感图：{fig_dir / 'partition_sentiment.png'}")
    print(f"- 高频词图：{fig_dir / 'keywords_top15.png'}")


def normalize_review_input(value):
    value = value.strip()
    mapping = {
        "1": "1", "正": "1", "正面": "1",
        "0": "0", "中": "0", "中性": "0",
        "-1": "-1", "负": "-1", "负面": "-1",
    }
    return mapping.get(value)


def ask_review_labels(review_path, max_questions=MAX_REVIEW_QUESTIONS):
    review_path = Path(review_path)
    df = pd.read_csv(review_path, encoding="utf-8-sig")
    if "review_label" not in df.columns:
        print(f"跳过复核：{review_path} 缺少 review_label 列")
        return 0
    df["review_label"] = df["review_label"].astype("object")

    blank = df["review_label"].isna() | df["review_label"].astype(str).str.strip().eq("")
    indices = list(df[blank].head(max_questions).index)
    if not indices:
        print("本轮没有需要人工复核的空白样本。")
        return 0

    print("\n开始人工复核。输入规则：1=正面，0=中性，-1=负面；直接回车跳过；输入 q 结束本轮复核。")
    print("已人工标注过的弹幕不会重复出现；人工标签会作为最高优先级训练数据。")
    print("明显含“哈哈/笑死/牛/爱了”等正向口语、且没有负向冲突的样本会自动判正面，不再占用复核名额。")
    print(f"本轮最多复核 {len(indices)} 条。")

    labeled = 0
    for order, idx in enumerate(indices, start=1):
        row = df.loc[idx]
        print("\n" + "-" * 60)
        print(f"[{order}/{len(indices)}] {row.get('partition', '')} | {row.get('review_reason', '')}")
        print(f"弹幕：{row.get('text', '')}")
        print(
            "当前预测："
            f"{row.get('pred_label', '')}；"
            f"正={row.get('prob_positive', '')}，"
            f"中={row.get('prob_neutral', '')}，"
            f"负={row.get('prob_negative', '')}"
        )

        while True:
            answer = input("你的标注 1/0/-1：").strip()
            if answer.lower() == "q":
                df.to_csv(review_path, index=False, encoding="utf-8-sig")
                print(f"已保存 {labeled} 条标注：{review_path}")
                return labeled
            if answer == "":
                break
            normalized = normalize_review_input(answer)
            if normalized is not None:
                df.at[idx, "review_label"] = normalized
                labeled += 1
                df.to_csv(review_path, index=False, encoding="utf-8-sig")
                break
            print("输入无效，请输入 1、0、-1；回车跳过；q 结束。")

    df.to_csv(review_path, index=False, encoding="utf-8-sig")
    print(f"\n本轮已保存 {labeled} 条人工标注：{review_path}")
    return labeled


def main():
    print("=" * 60)
    print("B站弹幕情感分析四轮主动学习实验")
    print("=" * 60)
    experiment_name = safe_experiment_name(input("请输入本次实验名称（可直接回车使用时间戳）："))
    learning_bvid = ask_bvid("学习区")
    life_bvid = ask_bvid("生活区")

    data_dir = ROOT / "data" / "experiments" / experiment_name
    result_base_dir = ROOT / "results" / experiment_name
    fig_base_dir = ROOT / "figures" / experiment_name
    raw_path = data_dir / "raw_bilibili_danmu.csv"

    videos = [
        {"partition": "学习区", "bvid": learning_bvid},
        {"partition": "生活区", "bvid": life_bvid},
    ]

    print("\n[1/5] 开始爬取弹幕...")
    rows = crawl(videos=videos, out=raw_path, max_per_video=TARGET_PER_PARTITION)
    if not rows:
        raise RuntimeError("没有爬到任何弹幕，请检查 BV 号是否正确，或稍后重试。")
    crawl_stats = summarize_crawl(rows)
    print_crawl_requirement_note(crawl_stats)

    ensure_train_data()
    final_summary = None
    final_result_dir = None
    final_fig_dir = None

    for round_no in range(1, TOTAL_ROUNDS + 1):
        is_final = round_no == TOTAL_ROUNDS
        round_name = "final_round_4" if is_final else f"round_{round_no}"
        result_dir = result_base_dir / round_name
        fig_dir = fig_base_dir / round_name

        print("\n" + "=" * 60)
        print(f"[{round_no + 1}/5] 第 {round_no} 轮分析" + ("（最终轮）" if is_final else ""))
        print("=" * 60)
        summary = analyze(
            train_data_path=TRAIN_DATA_PATH,
            predict_data_path=raw_path,
            result_dir=result_dir,
            fig_dir=fig_dir,
        )
        write_summary(result_dir / "experiment_summary.txt", f"{experiment_name}/{round_name}", videos, raw_path, crawl_stats, summary)
        print_round_outputs(summary, result_dir, fig_dir, is_final=is_final)

        final_summary = summary
        final_result_dir = result_dir
        final_fig_dir = fig_dir

        if round_no <= REVIEW_ROUNDS:
            ask_review_labels(summary["review_path"], max_questions=MAX_REVIEW_QUESTIONS)

    print("\n" + "=" * 60)
    print("四轮主动学习实验完成，final_round_4 为最终结果。")
    print("=" * 60)
    print(f"- 原始弹幕：{raw_path}")
    print(f"- 最终结果目录：{final_result_dir}")
    print(f"- 最终图表目录：{final_fig_dir}")
    print(f"- 最终摘要：{final_summary['analysis_summary_path']}")
    print(f"- 最终分区统计：{final_result_dir / 'partition_sentiment_stats.csv'}")
    print(f"- 最终分区图：{final_fig_dir / 'partition_sentiment.png'}")


if __name__ == "__main__":
    main()
