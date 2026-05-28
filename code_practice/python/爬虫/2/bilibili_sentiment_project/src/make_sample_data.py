"""生成课堂演示用样例弹幕数据。真实项目请使用 crawler_bilibili.py 替换数据源。"""
from pathlib import Path
import random
import pandas as pd

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "data" / "danmu_sample_5000.csv"

learning_pos = [
    "老师讲得很清楚终于懂了", "这个方法太有用了收藏", "学会了感谢分享", "思路很清晰适合复习", "知识点总结很完整",
    "讲解细节很到位", "例题很经典收获很多", "这节课效率很高", "终于把公式理解了", "笔记已经记好了",
]
learning_neg = [
    "太难了完全听不懂", "备考压力好大想哭", "这个知识点让我崩溃", "越学越焦虑", "作业好多真的累",
    "讲得有点快跟不上", "看到题目就迷茫", "复习效率太低了", "这个公式太痛苦", "学不会有点烦",
]
life_pos = [
    "这个视频太治愈了", "生活感满满很温暖", "看完心情变好了", "好喜欢这种日常", "真的很放松",
    "画面好看点赞", "这种分享很真实", "快乐就是这么简单", "内容有趣支持", "看着很舒服",
]
life_neg = [
    "有点无聊看不下去", "内容太水了没用", "节奏太慢有点烦", "标题党无语", "感觉不太真实",
    "看完没什么收获", "评论区吵起来了", "剪辑有点乱", "体验一般", "有点尴尬",
]
mods = ["哈哈", "确实", "救命", "姐妹们", "同感", "第{}遍看", "期末人破防", "打卡{}", "三连了", "弹幕护体"]


def generate_sample_data(out=OUT):
    random.seed(42)
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)

    rows = []
    for i in range(2500):
        is_pos = random.random() < 0.42
        base = random.choice(learning_pos if is_pos else learning_neg)
        text = base + random.choice(mods).format(i % 97, i % 31)
        rows.append({"partition": "学习区", "bvid": f"learn_{i//500+1}", "text": text + f"#{i}", "true_sentiment": 1 if is_pos else 0})
    for i in range(2500):
        is_pos = random.random() < 0.68
        base = random.choice(life_pos if is_pos else life_neg)
        text = base + random.choice(mods).format(i % 97, i % 31)
        rows.append({"partition": "生活区", "bvid": f"life_{i//500+1}", "text": text + f"#{i}", "true_sentiment": 1 if is_pos else 0})

    random.shuffle(rows)
    df = pd.DataFrame(rows)
    # 模拟人工标注1000条；其余留空，由模型自动预测。
    df["label"] = ""
    label_idx = df.groupby("partition", group_keys=False).sample(n=500, random_state=123).index
    # 加入少量人工标注噪声，使结果更接近真实短文本任务。
    labels = df.loc[label_idx, "true_sentiment"].copy()
    noise_idx = labels.sample(frac=0.06, random_state=77).index
    labels.loc[noise_idx] = 1 - labels.loc[noise_idx]
    labels = labels.map({1: 1, 0: -1})
    df.loc[label_idx, "label"] = labels.astype(int)
    df.drop(columns=["true_sentiment"]).to_csv(out, index=False, encoding="utf-8-sig")
    print(f"saved {out}, rows={len(df)}, labeled={df['label'].ne('').sum()}")
    return out


if __name__ == "__main__":
    generate_sample_data()
