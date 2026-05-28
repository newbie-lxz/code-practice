# -*- coding: utf-8 -*-
"""
注释阅读版：make_sample_data.py

负责生成课堂演示用样例数据，真实实验主要依赖 crawler_bilibili.py 爬到的数据。

注意：
1. 本文件只用于阅读理解，正式运行请使用 src 目录里的原文件。
2. 每段代码前面的 '# 注释：' 是对下一行或下一小段代码的解释。
3. 读完可以直接删除整个 annotated_code 文件夹，不影响项目。
"""

# 注释：这里是文档字符串，用自然语言说明当前文件或函数的用途。
"""生成课堂演示用样例弹幕数据。真实项目请使用 crawler_bilibili.py 替换数据源。"""
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from pathlib import Path
# 注释：导入 random，供后续代码调用。
import random
# 注释：导入 pandas as pd，供后续代码调用。
import pandas as pd

# 注释：定位项目根目录。
ROOT = Path(__file__).resolve().parents[1]
# 注释：设置默认输出文件路径。
OUT = ROOT / "data" / "danmu_sample_5000.csv"

# 注释：给变量 learning_pos 赋值，供后续步骤使用。
learning_pos = [
    # 注释：这是列表、字典或函数参数中的一项。
    "老师讲得很清楚终于懂了", "这个方法太有用了收藏", "学会了感谢分享", "思路很清晰适合复习", "知识点总结很完整",
    # 注释：这是列表、字典或函数参数中的一项。
    "讲解细节很到位", "例题很经典收获很多", "这节课效率很高", "终于把公式理解了", "笔记已经记好了",
# 注释：结束上面开启的列表、字典、元组或函数调用。
]
# 注释：给变量 learning_neg 赋值，供后续步骤使用。
learning_neg = [
    # 注释：这是列表、字典或函数参数中的一项。
    "太难了完全听不懂", "备考压力好大想哭", "这个知识点让我崩溃", "越学越焦虑", "作业好多真的累",
    # 注释：这是列表、字典或函数参数中的一项。
    "讲得有点快跟不上", "看到题目就迷茫", "复习效率太低了", "这个公式太痛苦", "学不会有点烦",
# 注释：结束上面开启的列表、字典、元组或函数调用。
]
# 注释：给变量 life_pos 赋值，供后续步骤使用。
life_pos = [
    # 注释：这是列表、字典或函数参数中的一项。
    "这个视频太治愈了", "生活感满满很温暖", "看完心情变好了", "好喜欢这种日常", "真的很放松",
    # 注释：这是列表、字典或函数参数中的一项。
    "画面好看点赞", "这种分享很真实", "快乐就是这么简单", "内容有趣支持", "看着很舒服",
# 注释：结束上面开启的列表、字典、元组或函数调用。
]
# 注释：给变量 life_neg 赋值，供后续步骤使用。
life_neg = [
    # 注释：这是列表、字典或函数参数中的一项。
    "有点无聊看不下去", "内容太水了没用", "节奏太慢有点烦", "标题党无语", "感觉不太真实",
    # 注释：这是列表、字典或函数参数中的一项。
    "看完没什么收获", "评论区吵起来了", "剪辑有点乱", "体验一般", "有点尴尬",
# 注释：结束上面开启的列表、字典、元组或函数调用。
]
# 注释：给变量 mods 赋值，供后续步骤使用。
mods = ["哈哈", "确实", "救命", "姐妹们", "同感", "第{}遍看", "期末人破防", "打卡{}", "三连了", "弹幕护体"]


# 注释：生成 5000 条演示弹幕，并抽取 1000 条作为模拟人工标注。
def generate_sample_data(out=OUT):
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    random.seed(42)
    # 注释：给变量 out 赋值，供后续步骤使用。
    out = Path(out)
    # 注释：创建目录；parents=True 时会自动创建不存在的上级目录。
    out.parent.mkdir(parents=True, exist_ok=True)

    # 注释：给变量 rows 赋值，供后续步骤使用。
    rows = []
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for i in range(2500):
        # 注释：给变量 is_pos 赋值，供后续步骤使用。
        is_pos = random.random() < 0.42
        # 注释：给变量 base 赋值，供后续步骤使用。
        base = random.choice(learning_pos if is_pos else learning_neg)
        # 注释：给变量 text 赋值，供后续步骤使用。
        text = base + random.choice(mods).format(i % 97, i % 31)
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        rows.append({"partition": "学习区", "bvid": f"learn_{i//500+1}", "text": text + f"#{i}", "true_sentiment": 1 if is_pos else 0})
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for i in range(2500):
        # 注释：给变量 is_pos 赋值，供后续步骤使用。
        is_pos = random.random() < 0.68
        # 注释：给变量 base 赋值，供后续步骤使用。
        base = random.choice(life_pos if is_pos else life_neg)
        # 注释：给变量 text 赋值，供后续步骤使用。
        text = base + random.choice(mods).format(i % 97, i % 31)
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        rows.append({"partition": "生活区", "bvid": f"life_{i//500+1}", "text": text + f"#{i}", "true_sentiment": 1 if is_pos else 0})

    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    random.shuffle(rows)
    # 注释：给变量 df 赋值，供后续步骤使用。
    df = pd.DataFrame(rows)
    # 模拟人工标注1000条；其余留空，由模型自动预测。
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    df["label"] = ""
    # 注释：按指定字段分组统计数据。
    label_idx = df.groupby("partition", group_keys=False).sample(n=500, random_state=123).index
    # 加入少量人工标注噪声，使结果更接近真实短文本任务。
    # 注释：给变量 labels 赋值，供后续步骤使用。
    labels = df.loc[label_idx, "true_sentiment"].copy()
    # 注释：给变量 noise_idx 赋值，供后续步骤使用。
    noise_idx = labels.sample(frac=0.06, random_state=77).index
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    labels.loc[noise_idx] = 1 - labels.loc[noise_idx]
    # 注释：对一列或一行批量应用函数，生成新结果。
    labels = labels.map({1: 1, 0: -1})
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    df.loc[label_idx, "label"] = labels.astype(int)
    # 注释：把 DataFrame 保存为 CSV 文件。
    df.drop(columns=["true_sentiment"]).to_csv(out, index=False, encoding="utf-8-sig")
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"saved {out}, rows={len(df)}, labeled={df['label'].ne('').sum()}")
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return out


# 注释：判断当前文件是否被直接运行；直接运行时才启动主流程。
if __name__ == "__main__":
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    generate_sample_data()
