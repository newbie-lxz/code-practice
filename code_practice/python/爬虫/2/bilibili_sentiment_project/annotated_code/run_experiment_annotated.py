# -*- coding: utf-8 -*-
"""
注释阅读版：run_experiment.py

项目一键入口，串起爬虫、训练分析、人工复核、四轮主动学习和最终结果归档。

注意：
1. 本文件只用于阅读理解，正式运行请使用 src 目录里的原文件。
2. 每段代码前面的 '# 注释：' 是对下一行或下一小段代码的解释。
3. 读完可以直接删除整个 annotated_code 文件夹，不影响项目。
"""

# 注释：这里是文档字符串，用自然语言说明当前文件或函数的用途。
"""
一键实验脚本。
运行后输入学习区和生活区 BV 号，程序会自动完成：爬取弹幕 -> 训练模型 -> 预测分析 -> 生成结果和图表。
运行：python src/run_experiment.py
"""
# 注释：导入 re，供后续代码调用。
import re
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from collections import Counter
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from datetime import datetime
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from pathlib import Path

# 注释：导入 pandas as pd，供后续代码调用。
import pandas as pd

# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from crawler_bilibili import crawl
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from make_sample_data import generate_sample_data
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from train_analyze import ROOT, TRAIN_DATA_PATH, analyze

# 注释：记录作业目标总弹幕量。
TARGET_TOTAL = 5000
# 注释：记录每个分区的目标弹幕量。
TARGET_PER_PARTITION = 2500
# 注释：设置主动学习总轮数。
TOTAL_ROUNDS = 4
# 注释：设置需要人工复核的轮数。
REVIEW_ROUNDS = 3
# 注释：限制每轮最多人工标注数量。
MAX_REVIEW_QUESTIONS = 100


# 注释：从用户输入的 BV 号或视频链接中提取真正的 BV 编号。
def extract_bvid(value: str) -> str:
    # 注释：给变量 value 赋值，供后续步骤使用。
    value = value.strip()
    # 注释：给变量 match 赋值，供后续步骤使用。
    match = re.search(r"BV[A-Za-z0-9]+", value)
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return match.group(0) if match else value


# 注释：在终端循环询问某个分区的 BV 号，直到格式正确。
def ask_bvid(partition: str) -> str:
    # 注释：循环结构：只要条件满足，就持续执行下面的逻辑。
    while True:
        # 注释：读取用户在终端输入的内容。
        bvid = extract_bvid(input(f"请输入{partition}视频 BV 号或视频链接："))
        # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
        if bvid.startswith("BV") and len(bvid) >= 8:
            # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
            return bvid
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("输入格式不太对，请输入类似 BV1BiDaB1EEN 的 BV 号，或直接粘贴 B 站视频链接。")


# 注释：把实验名称清洗成安全的文件夹名。
def safe_experiment_name(name: str) -> str:
    # 注释：给变量 default_name 赋值，供后续步骤使用。
    default_name = datetime.now().strftime("experiment_%Y%m%d_%H%M%S")
    # 注释：给变量 name 赋值，供后续步骤使用。
    name = name.strip() or default_name
    # 注释：给变量 name 赋值，供后续步骤使用。
    name = re.sub(r'[<>:"/\\|?*\s]+', "_", name).strip("._")
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return name or default_name


# 注释：把本轮实验的重要路径、指标和统计写入 experiment_summary.txt。
def write_summary(path: Path, experiment_name: str, videos, raw_path: Path, crawl_stats, summary) -> None:
    # 注释：给变量 metrics 赋值，供后续步骤使用。
    metrics = summary["metrics"]
    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = summary["stat"]
    # 注释：给变量 lines 赋值，供后续步骤使用。
    lines = [
        # 注释：这是列表、字典或函数参数中的一项。
        f"实验名称：{experiment_name}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"实验时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        "输入视频：",
    # 注释：结束上面开启的列表、字典、元组或函数调用。
    ]
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for item in videos:
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        lines.append(f"- {item['partition']}：{item['bvid']}")
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    lines.extend([
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        f"原始弹幕：{raw_path}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"采集总量：{crawl_stats['total']} / 目标 {TARGET_TOTAL}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"学习区采集量：{crawl_stats['partition_counts'].get('学习区', 0)} / 目标 {TARGET_PER_PARTITION}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"生活区采集量：{crawl_stats['partition_counts'].get('生活区', 0)} / 目标 {TARGET_PER_PARTITION}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"训练数据：{summary['train_data_path']}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"预测数据：{summary['predict_path']}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"最优模型：{summary['best_model']}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"历史人工反馈样本数：{summary.get('feedback_count', 0)}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"中性种子样本数：{summary.get('neutral_seed_count', 0)}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"本轮待人工复核样本数：{summary.get('review_count', 0)}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"本轮复核抽样比例：{summary.get('review_ratio', 0):.0%}",
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        "模型指标：",
        # 注释：这是列表、字典或函数参数中的一项。
        metrics.to_string(index=False),
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        "分区情感统计：",
        # 注释：这是列表、字典或函数参数中的一项。
        stat.to_string(index=False),
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        f"结果目录：{summary['result_dir']}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"图表目录：{summary['fig_dir']}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"待复核样本：{summary.get('review_path', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"自动分析摘要：{summary.get('analysis_summary_path', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"低置信样本：{summary.get('diagnostics', {}).get('low_confidence_samples', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"词典模型冲突样本：{summary.get('diagnostics', {}).get('conflict_samples', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"按视频统计：{summary.get('diagnostics', {}).get('video_sentiment_stats', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        f"与上一轮对比：{summary.get('iteration_comparison_path', '')}",
        # 注释：这是列表、字典或函数参数中的一项。
        "",
        # 注释：这是列表、字典或函数参数中的一项。
        "按情感分类导出的弹幕：",
    # 注释：结束上面开启的列表、字典、元组或函数调用。
    ])
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for label, file_path in summary.get("label_group_paths", {}).items():
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        lines.append(f"- {label}：{file_path}")
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    path.write_text("\n".join(lines), encoding="utf-8")


# 注释：保证训练样例数据存在，不存在时自动生成。
def ensure_train_data() -> None:
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if TRAIN_DATA_PATH.exists():
        # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
        return
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"未找到训练样例数据：{TRAIN_DATA_PATH}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("正在自动生成课堂演示用标注样例数据...")
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    generate_sample_data(TRAIN_DATA_PATH)


# 注释：统计本次爬虫总量和各分区数量。
def summarize_crawl(rows):
    # 注释：给变量 counts 赋值，供后续步骤使用。
    counts = Counter(row["partition"] for row in rows)
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return {"total": len(rows), "partition_counts": dict(counts)}


# 注释：打印采集量和作业目标之间的差距。
def print_crawl_requirement_note(crawl_stats):
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"采集总量：{crawl_stats['total']} / 作业目标 {TARGET_TOTAL}")
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for partition in ["学习区", "生活区"]:
        # 注释：给变量 count 赋值，供后续步骤使用。
        count = crawl_stats["partition_counts"].get(partition, 0)
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(f"{partition}：{count} / 目标 {TARGET_PER_PARTITION}")
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if crawl_stats["total"] < TARGET_TOTAL:
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("提示：当前两个 BV 的可获取弹幕不足 5000 条，程序会先按实际数据完成分析；如需严格满 5000 条，请换弹幕更多的视频。")


# 注释：把本轮关键输出文件路径打印到终端。
def print_round_outputs(summary, result_dir, fig_dir, is_final=False):
    # 注释：给变量 title 赋值，供后续步骤使用。
    title = "最终结果" if is_final else "本轮结果"
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"\n{title}输出：")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 分析结果：{result_dir}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 图表文件：{fig_dir}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 自动分析摘要：{summary['analysis_summary_path']}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 分区统计：{result_dir / 'partition_sentiment_stats.csv'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 正面弹幕：{result_dir / 'positive_comments.csv'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 负面弹幕：{result_dir / 'negative_comments.csv'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 中性弹幕：{result_dir / 'neutral_comments.csv'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 待人工复核：{summary['review_path']}（约 {summary['review_ratio']:.0%}，共 {summary['review_count']} 条）")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 分区情感图：{fig_dir / 'partition_sentiment.png'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 高频词图：{fig_dir / 'keywords_top15.png'}")


# 注释：把人工输入的 1/0/-1 或中文标签统一成标准标签。
def normalize_review_input(value):
    # 注释：给变量 value 赋值，供后续步骤使用。
    value = value.strip()
    # 注释：给变量 mapping 赋值，供后续步骤使用。
    mapping = {
        # 注释：这是列表、字典或函数参数中的一项。
        "1": "1", "正": "1", "正面": "1",
        # 注释：这是列表、字典或函数参数中的一项。
        "0": "0", "中": "0", "中性": "0",
        # 注释：这是列表、字典或函数参数中的一项。
        "-1": "-1", "负": "-1", "负面": "-1",
    # 注释：结束上面开启的列表、字典、元组或函数调用。
    }
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return mapping.get(value)


# 注释：在终端逐条显示待复核样本，并把你的人工标签写回 CSV。
def ask_review_labels(review_path, max_questions=MAX_REVIEW_QUESTIONS):
    # 注释：给变量 review_path 赋值，供后续步骤使用。
    review_path = Path(review_path)
    # 注释：读取 CSV 文件为 pandas DataFrame。
    df = pd.read_csv(review_path, encoding="utf-8-sig")
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if "review_label" not in df.columns:
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(f"跳过复核：{review_path} 缺少 review_label 列")
        # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
        return 0
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    df["review_label"] = df["review_label"].astype("object")

    # 注释：给变量 blank 赋值，供后续步骤使用。
    blank = df["review_label"].isna() | df["review_label"].astype(str).str.strip().eq("")
    # 注释：取排序后的前几条数据。
    indices = list(df[blank].head(max_questions).index)
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if not indices:
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("本轮没有需要人工复核的空白样本。")
        # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
        return 0

    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("\n开始人工复核。输入规则：1=正面，0=中性，-1=负面；直接回车跳过；输入 q 结束本轮复核。")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("已人工标注过的弹幕不会重复出现；人工标签会作为最高优先级训练数据。")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("明显含“哈哈/笑死/牛/爱了”等正向口语、且没有负向冲突的样本会自动判正面，不再占用复核名额。")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"本轮最多复核 {len(indices)} 条。")

    # 注释：给变量 labeled 赋值，供后续步骤使用。
    labeled = 0
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for order, idx in enumerate(indices, start=1):
        # 注释：给变量 row 赋值，供后续步骤使用。
        row = df.loc[idx]
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("\n" + "-" * 60)
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(f"[{order}/{len(indices)}] {row.get('partition', '')} | {row.get('review_reason', '')}")
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(f"弹幕：{row.get('text', '')}")
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            "当前预测："
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            f"{row.get('pred_label', '')}；"
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            f"正={row.get('prob_positive', '')}，"
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            f"中={row.get('prob_neutral', '')}，"
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            f"负={row.get('prob_negative', '')}"
        # 注释：结束上面开启的列表、字典、元组或函数调用。
        )

        # 注释：循环结构：只要条件满足，就持续执行下面的逻辑。
        while True:
            # 注释：读取用户在终端输入的内容。
            answer = input("你的标注 1/0/-1：").strip()
            # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
            if answer.lower() == "q":
                # 注释：把 DataFrame 保存为 CSV 文件。
                df.to_csv(review_path, index=False, encoding="utf-8-sig")
                # 注释：向终端输出提示信息，方便观察程序运行进度。
                print(f"已保存 {labeled} 条标注：{review_path}")
                # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
                return labeled
            # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
            if answer == "":
                # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
                break
            # 注释：读取用户在终端输入的内容。
            normalized = normalize_review_input(answer)
            # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
            if normalized is not None:
                # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
                df.at[idx, "review_label"] = normalized
                # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
                labeled += 1
                # 注释：把 DataFrame 保存为 CSV 文件。
                df.to_csv(review_path, index=False, encoding="utf-8-sig")
                # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
                break
            # 注释：向终端输出提示信息，方便观察程序运行进度。
            print("输入无效，请输入 1、0、-1；回车跳过；q 结束。")

    # 注释：把 DataFrame 保存为 CSV 文件。
    df.to_csv(review_path, index=False, encoding="utf-8-sig")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"\n本轮已保存 {labeled} 条人工标注：{review_path}")
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return labeled


# 注释：脚本主流程入口。
def main():
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("=" * 60)
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("B站弹幕情感分析四轮主动学习实验")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("=" * 60)
    # 注释：读取用户在终端输入的内容。
    experiment_name = safe_experiment_name(input("请输入本次实验名称（可直接回车使用时间戳）："))
    # 注释：给变量 learning_bvid 赋值，供后续步骤使用。
    learning_bvid = ask_bvid("学习区")
    # 注释：给变量 life_bvid 赋值，供后续步骤使用。
    life_bvid = ask_bvid("生活区")

    # 注释：给变量 data_dir 赋值，供后续步骤使用。
    data_dir = ROOT / "data" / "experiments" / experiment_name
    # 注释：给变量 result_base_dir 赋值，供后续步骤使用。
    result_base_dir = ROOT / "results" / experiment_name
    # 注释：给变量 fig_base_dir 赋值，供后续步骤使用。
    fig_base_dir = ROOT / "figures" / experiment_name
    # 注释：给变量 raw_path 赋值，供后续步骤使用。
    raw_path = data_dir / "raw_bilibili_danmu.csv"

    # 注释：给变量 videos 赋值，供后续步骤使用。
    videos = [
        # 注释：这是列表、字典或函数参数中的一项。
        {"partition": "学习区", "bvid": learning_bvid},
        # 注释：这是列表、字典或函数参数中的一项。
        {"partition": "生活区", "bvid": life_bvid},
    # 注释：结束上面开启的列表、字典、元组或函数调用。
    ]

    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("\n[1/5] 开始爬取弹幕...")
    # 注释：给变量 rows 赋值，供后续步骤使用。
    rows = crawl(videos=videos, out=raw_path, max_per_video=TARGET_PER_PARTITION)
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if not rows:
        # 注释：主动抛出错误，让调用者知道当前流程无法继续。
        raise RuntimeError("没有爬到任何弹幕，请检查 BV 号是否正确，或稍后重试。")
    # 注释：给变量 crawl_stats 赋值，供后续步骤使用。
    crawl_stats = summarize_crawl(rows)
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print_crawl_requirement_note(crawl_stats)

    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    ensure_train_data()
    # 注释：给变量 final_summary 赋值，供后续步骤使用。
    final_summary = None
    # 注释：给变量 final_result_dir 赋值，供后续步骤使用。
    final_result_dir = None
    # 注释：给变量 final_fig_dir 赋值，供后续步骤使用。
    final_fig_dir = None

    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for round_no in range(1, TOTAL_ROUNDS + 1):
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        is_final = round_no == TOTAL_ROUNDS
        # 注释：给变量 round_name 赋值，供后续步骤使用。
        round_name = "final_round_4" if is_final else f"round_{round_no}"
        # 注释：给变量 result_dir 赋值，供后续步骤使用。
        result_dir = result_base_dir / round_name
        # 注释：给变量 fig_dir 赋值，供后续步骤使用。
        fig_dir = fig_base_dir / round_name

        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("\n" + "=" * 60)
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print(f"[{round_no + 1}/5] 第 {round_no} 轮分析" + ("（最终轮）" if is_final else ""))
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print("=" * 60)
        # 注释：给变量 summary 赋值，供后续步骤使用。
        summary = analyze(
            # 注释：给变量 train_data_path 赋值，供后续步骤使用。
            train_data_path=TRAIN_DATA_PATH,
            # 注释：给变量 predict_data_path 赋值，供后续步骤使用。
            predict_data_path=raw_path,
            # 注释：给变量 result_dir 赋值，供后续步骤使用。
            result_dir=result_dir,
            # 注释：给变量 fig_dir 赋值，供后续步骤使用。
            fig_dir=fig_dir,
        # 注释：结束上面开启的列表、字典、元组或函数调用。
        )
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        write_summary(result_dir / "experiment_summary.txt", f"{experiment_name}/{round_name}", videos, raw_path, crawl_stats, summary)
        # 注释：向终端输出提示信息，方便观察程序运行进度。
        print_round_outputs(summary, result_dir, fig_dir, is_final=is_final)

        # 注释：给变量 final_summary 赋值，供后续步骤使用。
        final_summary = summary
        # 注释：给变量 final_result_dir 赋值，供后续步骤使用。
        final_result_dir = result_dir
        # 注释：给变量 final_fig_dir 赋值，供后续步骤使用。
        final_fig_dir = fig_dir

        # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
        if round_no <= REVIEW_ROUNDS:
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            ask_review_labels(summary["review_path"], max_questions=MAX_REVIEW_QUESTIONS)

    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("\n" + "=" * 60)
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("四轮主动学习实验完成，final_round_4 为最终结果。")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print("=" * 60)
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 原始弹幕：{raw_path}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 最终结果目录：{final_result_dir}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 最终图表目录：{final_fig_dir}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 最终摘要：{final_summary['analysis_summary_path']}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 最终分区统计：{final_result_dir / 'partition_sentiment_stats.csv'}")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"- 最终分区图：{final_fig_dir / 'partition_sentiment.png'}")


# 注释：判断当前文件是否被直接运行；直接运行时才启动主流程。
if __name__ == "__main__":
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    main()
