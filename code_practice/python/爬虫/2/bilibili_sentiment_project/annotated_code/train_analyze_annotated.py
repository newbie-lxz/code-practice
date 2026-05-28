# -*- coding: utf-8 -*-
"""
注释阅读版：train_analyze.py

这是项目核心分析程序的阅读版，只用于理解代码。
正式运行请使用 src/train_analyze.py 或 src/run_experiment.py。
"""

# 注释：文档字符串，说明当前文件或函数的用途。
"""
B站学习区/生活区弹幕情感对比分析主程序。
功能：清洗、分词、词典情感特征、TF-IDF、四类机器学习模型训练、全量预测、可视化。
运行：python src/train_analyze.py
"""
# 注释：导入标准库或第三方库，供后续代码使用。
import re
# 注释：从指定模块导入需要的类或函数。
from pathlib import Path

# 注释：导入标准库或第三方库，供后续代码使用。
import matplotlib
# 注释：导入标准库或第三方库，供后续代码使用。
import numpy as np
# 注释：导入标准库或第三方库，供后续代码使用。
import pandas as pd

matplotlib.use("Agg")
# 注释：导入标准库或第三方库，供后续代码使用。
import matplotlib.pyplot as plt
# 注释：从指定模块导入需要的类或函数。
from matplotlib import font_manager
# 注释：从指定模块导入需要的类或函数。
from scipy.sparse import hstack, csr_matrix
# 注释：从指定模块导入需要的类或函数。
from sklearn.ensemble import RandomForestClassifier
# 注释：从指定模块导入需要的类或函数。
from sklearn.feature_extraction.text import TfidfVectorizer
# 注释：从指定模块导入需要的类或函数。
from sklearn.linear_model import LogisticRegression
# 注释：从指定模块导入需要的类或函数。
from sklearn.metrics import accuracy_score, f1_score, classification_report, confusion_matrix
# 注释：从指定模块导入需要的类或函数。
from sklearn.model_selection import train_test_split
# 注释：从指定模块导入需要的类或函数。
from sklearn.naive_bayes import MultinomialNB
# 注释：从指定模块导入需要的类或函数。
from sklearn.svm import LinearSVC

# 注释：给变量 ROOT 赋值，供后续步骤使用。
ROOT = Path(__file__).resolve().parents[1]
# 注释：给变量 TRAIN_DATA_PATH 赋值，供后续步骤使用。
TRAIN_DATA_PATH = ROOT / "data" / "danmu_sample_5000.csv"
# 注释：给变量 RAW_DATA_PATH 赋值，供后续步骤使用。
RAW_DATA_PATH = ROOT / "data" / "raw_bilibili_danmu.csv"
# 注释：给变量 LEXICON_DIR 赋值，供后续步骤使用。
LEXICON_DIR = ROOT / "data" / "sentiment_lexicon"
# 注释：给变量 FEEDBACK_DIR 赋值，供后续步骤使用。
FEEDBACK_DIR = ROOT / "data" / "feedback"
# 注释：给变量 RESULT_DIR 赋值，供后续步骤使用。
RESULT_DIR = ROOT / "results"
# 注释：给变量 FIG_DIR 赋值，供后续步骤使用。
FIG_DIR = ROOT / "figures"
RESULT_DIR.mkdir(exist_ok=True)
FIG_DIR.mkdir(exist_ok=True)

# 注释：尝试执行可能出错的代码。
try:
    # 注释：导入标准库或第三方库，供后续代码使用。
    import jieba
    # 注释：定义函数 tokenize，封装一段可复用逻辑。
    def tokenize(text: str):
        # 注释：返回当前函数的结果。
        return [w for w in jieba.lcut(text) if w.strip()]
# 注释：处理 try 中出现的异常。
except Exception:
    # 无 jieba 环境下的降级方案：中文按字/英文按词切分，保证程序可运行。
    # 注释：定义函数 tokenize，封装一段可复用逻辑。
    def tokenize(text: str):
        # 注释：返回当前函数的结果。
        return re.findall(r"[\u4e00-\u9fa5]|[A-Za-z0-9]+", str(text))

# 这里不是完整 HowNet/知网词典，只是程序内置的兜底小词表。
# 完整正负词典会在 load_sentiment_words() 中从 data/sentiment_lexicon/*.txt 自动读取并合并。
# 注释：内置正面兜底小词表，不是完整词典。
DEFAULT_POS_WORDS = set("""
懂了 清楚 有用 喜欢 厉害 高效 开心 治愈 放松 好看 赞 支持 学会 收获 真实 温暖 快乐
牛 绝了 牛逼 太强 好棒 可爱 爱了 宝藏 感动 泪目 笑死 哈哈 舒服 优秀 精彩 认真
靠谱 方便 简单 明白 详细 到位 完整 经典 推荐 收藏 三连 感谢 谢谢 666 nb yyds
""".split())
# 注释：内置负面兜底小词表，不是完整词典。
DEFAULT_NEG_WORDS = set("""
难 焦虑 崩溃 听不懂 烦 压力 困 想哭 无语 枯燥 累 失败 迷茫 拖延 痛苦 没用
烂 差 尬 假 恶心 难受 下头 失望 生气 吵 乱 崩 坏 无聊 看不下去 水 标题党
离谱 破防 问题 错误 垃圾 拉胯 折磨 麻烦 讨厌 别扭
""".split())
# 注释：停用词集合。
STOP_WORDS = set("的 了 啊 呀 呢 吗 吧 和 是 我 你 他 她 它 这 那 一个 一下 真的 有点".split())
# 注释：否定词集合，用于反转情感极性。
NEGATION_WORDS = set("不 没 无 非 未 别 莫 否 不是 没有 无法 不会 不想 不要 别再".split())
# 注释：程度副词权重表。
DEGREE_WORDS = {
    "极其": 2.2, "超级": 2.0, "非常": 2.0, "特别": 1.8, "太": 1.8,
    "很": 1.5, "真": 1.4, "挺": 1.3, "比较": 1.2, "有点": 0.8, "稍微": 0.7,
}
# 注释：给变量 SENTIMENT_COLUMNS 赋值，供后续步骤使用。
SENTIMENT_COLUMNS = [
    "pos_cnt", "neg_cnt", "word_len", "exclaim_cnt", "question_cnt",
    "lexicon_score", "lexicon_pos_score", "lexicon_neg_score", "lexicon_abs_score", "sentiment_density",
]
# 注释：给变量 FEATURE_COLUMNS 赋值，供后续步骤使用。
FEATURE_COLUMNS = [
    "pos_cnt", "neg_cnt", "word_len", "exclaim_cnt", "question_cnt",
    "lexicon_pos_score", "lexicon_neg_score", "lexicon_abs_score", "sentiment_density",
]
# 注释：给变量 WORD_TFIDF_MAX_FEATURES 赋值，供后续步骤使用。
WORD_TFIDF_MAX_FEATURES = 1500
# 注释：给变量 CHAR_TFIDF_MAX_FEATURES 赋值，供后续步骤使用。
CHAR_TFIDF_MAX_FEATURES = 2500
# 注释：给变量 LEXICON_STRONG_THRESHOLD 赋值，供后续步骤使用。
LEXICON_STRONG_THRESHOLD = 1.0
# 注释：给变量 MODEL_CONFIDENCE_THRESHOLD 赋值，供后续步骤使用。
MODEL_CONFIDENCE_THRESHOLD = 0.66
# 注释：给变量 NEUTRAL_CONFIDENCE_THRESHOLD 赋值，供后续步骤使用。
NEUTRAL_CONFIDENCE_THRESHOLD = 0.6
# 注释：给变量 NEUTRAL_STRICT_THRESHOLD 赋值，供后续步骤使用。
NEUTRAL_STRICT_THRESHOLD = 0.75
# 注释：给变量 NEUTRAL_SHORT_TEXT_THRESHOLD 赋值，供后续步骤使用。
NEUTRAL_SHORT_TEXT_THRESHOLD = 0.68
# 注释：给变量 MODEL_STRONG_THRESHOLD 赋值，供后续步骤使用。
MODEL_STRONG_THRESHOLD = 0.85
# 注释：给变量 REVIEW_SAMPLE_RATIO 赋值，供后续步骤使用。
REVIEW_SAMPLE_RATIO = 0.08
# 注释：给变量 MAX_REVIEW_SAMPLE_COUNT 赋值，供后续步骤使用。
MAX_REVIEW_SAMPLE_COUNT = 100
# 注释：给变量 LABEL_NAMES 赋值，供后续步骤使用。
LABEL_NAMES = {-1: "负面", 0: "中性", 1: "正面"}
# 注释：给变量 ORDERED_LABELS 赋值，供后续步骤使用。
ORDERED_LABELS = [-1, 0, 1]
# 注释：给变量 ORDERED_LABEL_NAMES 赋值，供后续步骤使用。
ORDERED_LABEL_NAMES = [LABEL_NAMES[i] for i in ORDERED_LABELS]
# 注释：给变量 LABEL_VALUES 赋值，供后续步骤使用。
LABEL_VALUES = {
    "-1": -1, "负": -1, "负面": -1, "消极": -1, "negative": -1, "neg": -1,
    "1": 1, "正": 1, "正面": 1, "积极": 1, "positive": 1, "pos": 1,
    "0": 0, "中": 0, "中性": 0, "无情绪": 0, "neutral": 0, "neu": 0,
    # 兼容旧版 2=中性 的历史人工标注。
    "2": 0,
}
# 注释：中性种子样本，用来增强模型对中性弹幕的识别。
NEUTRAL_SEED_TEXTS = [
    "打卡", "来了", "前排", "第一", "报到", "到此一游", "路过", "签到", "考古",
    "三连了", "收藏了", "弹幕护体", "已看", "看过", "复习一下", "再看一遍",
    "从首页来的", "老师来了", "同学来了", "有人吗", "这里人好多", "这是什么",
    "哪里下载", "求链接", "求资料", "求源码", "第1遍看", "第2遍看", "2024打卡",
    "2025打卡", "现在还有人看吗", "前方高能", "空降成功", "进度条撑住",
    "字幕来了", "听课中", "笔记中", "准备开始", "先收藏", "先缓存", "目录在哪",
    "这是第几集", "下节课见", "我来了我来了", "占个位置", "插眼", "马克一下",
    "看完再说", "路过看看", "学习记录", "今日学习", "继续学习", "开始学习",
    "数据库中的数据", "页面不是写死的", "这里是业务逻辑", "sql语句基础",
    "第一个函数", "看一下源码", "资料在哪", "笔记格式", "1.5倍速",
    "2倍速播放", "这个声音像孙悟空", "中杯大杯超大杯", "Java之父",
    "课程基础内容", "这是第几章", "视频速度控制", "md格式笔记",
]
# 注释：常见中性提示词，比如打卡、前排、求资料。
NEUTRAL_CUE_WORDS = set("打卡 来了 前排 第一 报到 到此一游 路过 签到 考古 插眼 马克 收藏 三连 弹幕 护体 求链接 求资料 求源码 目录 空降 字幕 复习 学习 测试 第一天 同款".split())
# 注释：技术/课程说明类中性提示词，比如数据、代码、倍速、笔记。
TECH_NEUTRAL_CUE_WORDS = set("""
数据 页面 数据库 网站 业务 逻辑 代码 函数 变量 对象 方法 类 接口 课程 视频 插件 倍速
资料 笔记 格式 文件 链接 源码 字幕 目录 声音 播放 速度 基础 章节 java mysql sql html css
python csdn edge md 软件 工程师 学院 学生 老师 同学
""".split())
# 注释：明显正向口语集合。
OBVIOUS_POSITIVE_CUE_WORDS = set("""
哈哈 哈哈哈 笑死 笑不活 乐死 好笑 搞笑 牛逼 太强 好棒 真棒 厉害 优秀 精彩 绝了
爱了 喜欢 舒服 爽 赞 yyds nb 666 好耶 学到了 学会了 干货 好兄弟
""".split())
# 注释：给变量 OBVIOUS_POSITIVE_PATTERNS 赋值，供后续步骤使用。
OBVIOUS_POSITIVE_PATTERNS = [
    re.compile(r"哈{2,}"),
    re.compile(r"h{2,}", re.IGNORECASE),
    re.compile(r"233+"),
    re.compile(r"6{3,}"),
    re.compile(r"(真|太|很|超级)?牛(啊|哇|呀|逼|的|了|!|！|$)"),
]
# 注释：明显负向口语集合。
OBVIOUS_NEGATIVE_CUE_WORDS = set("""
垃圾 恶心 烂 难受 下头 拉胯 看不下去 听不懂 无语 折磨 崩溃 烦 讨厌 尬 差 没用
入土 坐牢 裂开 破防 麻了 寄了 崩了 看不懂 学不会 不会 不行 太水
""".split())
# 注释：容易误伤的单字正面词，会从词典中剔除。
AMBIGUOUS_POSITIVE_WORDS = set("好 强 牛".split())
# 注释：容易误伤的单字负面词，会从词典中剔除。
AMBIGUOUS_NEGATIVE_WORDS = set("水".split())


# 注释：设置 matplotlib 中文字体，避免图表里的中文乱码。
def setup_chinese_font():
    # 注释：给变量 font_candidates 赋值，供后续步骤使用。
    font_candidates = [
        "C:/Windows/Fonts/msyh.ttc",      # Microsoft YaHei
        "C:/Windows/Fonts/simhei.ttf",    # SimHei
        "C:/Windows/Fonts/simsun.ttc",    # SimSun
        "/System/Library/Fonts/PingFang.ttc",
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
        "/usr/share/fonts/truetype/noto/NotoSansCJK-Regular.ttc",
    ]
    # 注释：循环处理一组数据。
    for font_path in font_candidates:
        # 注释：给变量 path 赋值，供后续步骤使用。
        path = Path(font_path)
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if path.exists():
            font_manager.fontManager.addfont(str(path))
            # 注释：给变量 font_name 赋值，供后续步骤使用。
            font_name = font_manager.FontProperties(fname=str(path)).get_name()
            plt.rcParams["font.sans-serif"] = [font_name]
            break
    plt.rcParams["axes.unicode_minus"] = False


# 注释：清洗弹幕文本，去掉链接、空白和无关符号。
def clean_text(text: str) -> str:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(text)
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = re.sub(r"http\S+|www\.\S+", "", text)
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = re.sub(r"\s+", "", text)
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = re.sub(r"[^\u4e00-\u9fa5A-Za-z0-9!?！？。,.，]", "", text)
    # 注释：返回当前函数的结果。
    return text


# 注释：读取情感词典文件，兼容 utf-8、utf-8-sig、gbk 编码。
def read_word_file(path):
    # 注释：给变量 words 赋值，供后续步骤使用。
    words = set()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not path.exists():
        # 注释：返回当前函数的结果。
        return words
    # 注释：循环处理一组数据。
    for encoding in ("utf-8-sig", "utf-8", "gbk"):
        # 注释：尝试执行可能出错的代码。
        try:
            # 注释：给变量 lines 赋值，供后续步骤使用。
            lines = path.read_text(encoding=encoding).splitlines()
            break
        # 注释：处理 try 中出现的异常。
        except UnicodeDecodeError:
            continue
    # 注释：兜底分支。
    else:
        # 注释：返回当前函数的结果。
        return words

    # 注释：循环处理一组数据。
    for line in lines:
        # 注释：给变量 word 赋值，供后续步骤使用。
        word = line.strip()
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if not word or word.startswith("#"):
            continue
        # 兼容 HowNet/知网词表中可能存在的空格、制表符、词性说明等格式。
        # 注释：给变量 word 赋值，供后续步骤使用。
        word = re.split(r"\s+", word)[0].strip()
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if word:
            words.add(word)
    # 注释：返回当前函数的结果。
    return words


# 注释：合并内置兜底词表和 data/sentiment_lexicon 里的 HowNet/知网词典。
def load_sentiment_words():
    # 注释：给变量 pos_files 赋值，供后续步骤使用。
    pos_files = [
        "hownet_positive.txt", "positive.txt", "pos.txt",
        "正面情感词语.txt", "正面评价词语.txt",
        "正面情感词语（中文）.txt", "正面评价词语（中文）.txt",
    ]
    # 注释：给变量 neg_files 赋值，供后续步骤使用。
    neg_files = [
        "hownet_negative.txt", "negative.txt", "neg.txt",
        "负面情感词语.txt", "负面评价词语.txt",
        "负面情感词语（中文）.txt", "负面评价词语（中文）.txt",
    ]
    # 注释：给变量 pos_words 赋值，供后续步骤使用。
    pos_words = set(DEFAULT_POS_WORDS)
    # 注释：给变量 neg_words 赋值，供后续步骤使用。
    neg_words = set(DEFAULT_NEG_WORDS)
    # 注释：循环处理一组数据。
    for filename in pos_files:
        pos_words.update(read_word_file(LEXICON_DIR / filename))
    # 注释：循环处理一组数据。
    for filename in neg_files:
        neg_words.update(read_word_file(LEXICON_DIR / filename))
    # 弹幕短文本里单字词很容易误伤，例如“好了”不一定正面，“水”也可能不是负面。
    pos_words.difference_update(AMBIGUOUS_POSITIVE_WORDS)
    neg_words.difference_update(AMBIGUOUS_NEGATIVE_WORDS)
    # 注释：返回当前函数的结果。
    return pos_words, neg_words


POS_WORDS, NEG_WORDS = load_sentiment_words()


# 注释：安全地把值转成浮点数，缺失或异常时给默认值。
def to_float(value, default=0.0):
    # 注释：尝试执行可能出错的代码。
    try:
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if pd.isna(value):
            # 注释：返回当前函数的结果。
            return default
        # 注释：返回当前函数的结果。
        return float(value)
    # 注释：处理 try 中出现的异常。
    except (TypeError, ValueError):
        # 注释：返回当前函数的结果。
        return default


# 注释：判断文本里是否出现明显正面口语，比如哈哈、笑死、学到了。
def contains_positive_cue(text: str) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(text).lower()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if any(word.lower() in text for word in OBVIOUS_POSITIVE_CUE_WORDS):
        # 注释：返回当前函数的结果。
        return True
    # 注释：返回当前函数的结果。
    return any(pattern.search(text) for pattern in OBVIOUS_POSITIVE_PATTERNS)


# 注释：判断文本里是否出现明显负面口语，比如入土、坐牢、看不懂。
def contains_negative_cue(text: str) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(text)
    # 注释：返回当前函数的结果。
    return any(word in text for word in OBVIOUS_NEGATIVE_CUE_WORDS)


# 注释：判断文本里是否出现打卡、资料、代码、倍速等偏中性的提示词。
def contains_neutral_cue(text: str) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(text).lower()
    # 注释：给变量 neutral_words 赋值，供后续步骤使用。
    neutral_words = NEUTRAL_CUE_WORDS | TECH_NEUTRAL_CUE_WORDS
    # 注释：返回当前函数的结果。
    return any(word.lower() in text for word in neutral_words)


# 注释：综合词典和概率，判断一条弹幕是否可以直接看作明显正面。
def has_obvious_positive_cue(row) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(row.get("text_clean", ""))
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not contains_positive_cue(text):
        # 注释：返回当前函数的结果。
        return False
    # 注释：给变量 score 赋值，供后续步骤使用。
    score = to_float(row.get("lexicon_score"))
    # 注释：给变量 neg_count 赋值，供后续步骤使用。
    neg_count = to_float(row.get("neg_cnt"))
    # 注释：给变量 negative_prob 赋值，供后续步骤使用。
    negative_prob = to_float(row.get("prob_negative"))
    # 注释：返回当前函数的结果。
    return score >= 0 and (neg_count == 0 or score >= LEXICON_STRONG_THRESHOLD) and negative_prob < 0.75


# 注释：综合词典和概率，判断一条弹幕是否可以直接看作明显负面。
def has_obvious_negative_cue(row) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(row.get("text_clean", ""))
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not contains_negative_cue(text):
        # 注释：返回当前函数的结果。
        return False
    # 注释：给变量 score 赋值，供后续步骤使用。
    score = to_float(row.get("lexicon_score"))
    # 注释：给变量 pos_count 赋值，供后续步骤使用。
    pos_count = to_float(row.get("pos_cnt"))
    # 注释：给变量 positive_prob 赋值，供后续步骤使用。
    positive_prob = to_float(row.get("prob_positive"))
    # 注释：返回当前函数的结果。
    return score <= 0 and (pos_count == 0 or score <= -LEXICON_STRONG_THRESHOLD) and positive_prob < 0.75


# 注释：保守中性判断：技术说明、打卡、资料类、低情绪弹幕优先保留中性。
def should_keep_neutral(row) -> bool:
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(row.get("text_clean", ""))
    # 注释：给变量 positive_prob 赋值，供后续步骤使用。
    positive_prob = to_float(row.get("prob_positive"))
    # 注释：给变量 negative_prob 赋值，供后续步骤使用。
    negative_prob = to_float(row.get("prob_negative"))
    # 注释：给变量 neutral_prob 赋值，供后续步骤使用。
    neutral_prob = to_float(row.get("prob_neutral"))
    # 注释：给变量 best_polar_prob 赋值，供后续步骤使用。
    best_polar_prob = max(positive_prob, negative_prob)
    # 注释：给变量 lexicon_abs 赋值，供后续步骤使用。
    lexicon_abs = to_float(row.get("lexicon_abs_score"))
    # 注释：给变量 raw_label 赋值，供后续步骤使用。
    raw_label = row.get("pred_raw_label", "")

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if has_obvious_positive_cue(row) or has_obvious_negative_cue(row):
        # 注释：返回当前函数的结果。
        return False

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if lexicon_abs == 0:
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if raw_label == "中性" and neutral_prob >= 0.42:
            # 注释：返回当前函数的结果。
            return True
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if neutral_prob >= 0.50 and neutral_prob >= best_polar_prob - 0.02:
            # 注释：返回当前函数的结果。
            return True
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if contains_neutral_cue(text) and neutral_prob >= 0.35 and best_polar_prob < 0.55:
            # 注释：返回当前函数的结果。
            return True
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if neutral_prob >= 0.35 and abs(positive_prob - negative_prob) < 0.15 and best_polar_prob < 0.45:
            # 注释：返回当前函数的结果。
            return True

    # 只有一个弱情感词，且模型明显偏中性时，不让词典把它硬拽到正/负面。
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if lexicon_abs <= 1 and raw_label == "中性" and neutral_prob >= 0.55 and best_polar_prob < 0.35:
        # 注释：返回当前函数的结果。
        return True

    # 注释：返回当前函数的结果。
    return False


# 注释：判断样本是否太明显，不需要进入人工复核池。
def is_obvious_auto_label(row) -> bool:
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if row.get("pred_label") == "正面" and has_obvious_positive_cue(row):
        # 注释：返回当前函数的结果。
        return True
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if row.get("pred_label") == "负面" and has_obvious_negative_cue(row):
        # 注释：返回当前函数的结果。
        return True
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if (
        row.get("pred_label") == "中性"
        and to_float(row.get("prob_neutral")) >= 0.85
        and to_float(row.get("lexicon_abs_score")) == 0
        and to_float(row.get("model_confidence")) >= 0.8
    ):
        # 注释：返回当前函数的结果。
        return True
    # 注释：返回当前函数的结果。
    return False


# 注释：把人工标签、旧版标签、中文标签统一成 -1/0/1。
def normalize_label(value, legacy_feedback_label=False):
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if pd.isna(value):
        # 注释：返回当前函数的结果。
        return np.nan
    # 注释：给变量 text 赋值，供后续步骤使用。
    text = str(value).strip().lower()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not text:
        # 注释：返回当前函数的结果。
        return np.nan
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if legacy_feedback_label:
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if text == "0":
            # 注释：返回当前函数的结果。
            return -1
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if text == "2":
            # 注释：返回当前函数的结果。
            return 0
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if text in LABEL_VALUES:
        # 注释：返回当前函数的结果。
        return LABEL_VALUES[text]
    # 注释：尝试执行可能出错的代码。
    try:
        # 注释：给变量 number 赋值，供后续步骤使用。
        number = int(float(text))
    # 注释：处理 try 中出现的异常。
    except ValueError:
        # 注释：返回当前函数的结果。
        return np.nan
    # 注释：返回当前函数的结果。
    return number if number in LABEL_NAMES else np.nan


# 注释：用情感词典计算正负词数量、情感分数、问号感叹号等特征。
def sentiment_features(text: str):
    # 注释：给变量 words 赋值，供后续步骤使用。
    words = [w for w in tokenize(text) if w not in STOP_WORDS]
    # 注释：给变量 pos 赋值，供后续步骤使用。
    pos = 0
    # 注释：给变量 neg 赋值，供后续步骤使用。
    neg = 0
    # 注释：给变量 score 赋值，供后续步骤使用。
    score = 0.0
    # 注释：给变量 pos_score 赋值，供后续步骤使用。
    pos_score = 0.0
    # 注释：给变量 neg_score 赋值，供后续步骤使用。
    neg_score = 0.0
    # 注释：给变量 matched_spans 赋值，供后续步骤使用。
    matched_spans = set()

    # 注释：循环处理一组数据。
    for i, word in enumerate(words):
        # 注释：给变量 polarity 赋值，供后续步骤使用。
        polarity = 1 if word in POS_WORDS else -1 if word in NEG_WORDS else 0
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if polarity == 0:
            continue
        # 注释：给变量 window 赋值，供后续步骤使用。
        window = words[max(0, i - 2):i]
        # 注释：给变量 weight 赋值，供后续步骤使用。
        weight = 1.0
        # 注释：循环处理一组数据。
        for prev in window:
            weight *= DEGREE_WORDS.get(prev, 1.0)
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if any(prev in NEGATION_WORDS for prev in window):
            polarity *= -1
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if polarity > 0:
            pos += 1
            pos_score += abs(weight)
        # 注释：兜底分支。
        else:
            neg += 1
            neg_score += abs(weight)
        score += polarity * weight

    # 处理 jieba 没切出来的多字情感词，例如“听不懂”“看不下去”“太强”。
    # 注释：循环处理一组数据。
    for lexicon, polarity in ((POS_WORDS, 1), (NEG_WORDS, -1)):
        # 注释：循环处理一组数据。
        for term in lexicon:
            # 注释：条件判断：满足条件时执行下面缩进的代码。
            if len(term) <= 1 or term not in text:
                continue
            # 注释：给变量 key 赋值，供后续步骤使用。
            key = (term, polarity)
            # 注释：条件判断：满足条件时执行下面缩进的代码。
            if key in matched_spans:
                continue
            matched_spans.add(key)
            # 注释：条件判断：满足条件时执行下面缩进的代码。
            if polarity > 0:
                pos += 1
                pos_score += 1.0
            # 注释：兜底分支。
            else:
                neg += 1
                neg_score += 1.0
            score += polarity

    # 注释：给变量 length 赋值，供后续步骤使用。
    length = len(words)
    # 注释：给变量 exclaim 赋值，供后续步骤使用。
    exclaim = text.count("!") + text.count("！")
    # 注释：给变量 question 赋值，供后续步骤使用。
    question = text.count("?") + text.count("？")
    # 注释：给变量 density 赋值，供后续步骤使用。
    density = (pos + neg) / max(length, 1)
    # 注释：返回当前函数的结果。
    return pos, neg, length, exclaim, question, score, pos_score, neg_score, abs(score), density


# 注释：清洗 DataFrame、规范标签、去重，并补充情感特征列。
def prepare_dataframe(df, legacy_binary_label=False):
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if "label" not in df.columns:
        df["label"] = np.nan
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if legacy_binary_label:
        # 注释：给变量 raw_label 赋值，供后续步骤使用。
        raw_label = df["label"].copy()
        # 注释：给变量 normalized 赋值，供后续步骤使用。
        normalized = raw_label.map(normalize_label)
        # 注释：给变量 legacy_negative 赋值，供后续步骤使用。
        legacy_negative = raw_label.astype(str).str.strip().eq("0")
        normalized.loc[legacy_negative] = -1
        df["label"] = normalized
    # 注释：兜底分支。
    else:
        df["label"] = df["label"].map(normalize_label)
    df["text_clean"] = df["text"].map(clean_text)
    # 注释：给变量 df 赋值，供后续步骤使用。
    df = df[df["text_clean"].str.len() > 0].drop_duplicates(["partition", "bvid", "text_clean"]).copy()
    # 注释：给变量 feats 赋值，供后续步骤使用。
    feats = df["text_clean"].map(sentiment_features)
    df[SENTIMENT_COLUMNS] = pd.DataFrame(feats.tolist(), index=df.index)
    # 注释：返回当前函数的结果。
    return df


# 注释：读取 CSV 并调用 prepare_dataframe 做统一预处理。
def load_and_prepare(path):
    # 注释：给变量 df 赋值，供后续步骤使用。
    df = pd.read_csv(path, encoding="utf-8-sig")
    # 注释：返回当前函数的结果。
    return prepare_dataframe(df, legacy_binary_label=Path(path).name == TRAIN_DATA_PATH.name)


# 注释：构造中性种子样本，帮助模型学会中性类别。
def make_neutral_seed_df():
    # 注释：给变量 rows 赋值，供后续步骤使用。
    rows = [
        {"partition": "中性种子", "bvid": "neutral_seed", "text": text, "label": 0}
        # 注释：循环处理一组数据。
        for text in NEUTRAL_SEED_TEXTS
    ]
    # 注释：返回当前函数的结果。
    return pd.DataFrame(rows)


# 注释：读取历史人工复核样本，作为下一轮训练数据。
def load_feedback_data(feedback_dir=FEEDBACK_DIR):
    # 注释：给变量 paths 赋值，供后续步骤使用。
    paths = []
    # 注释：给变量 feedback_dir 赋值，供后续步骤使用。
    feedback_dir = Path(feedback_dir)
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if feedback_dir.exists():
        paths.extend(feedback_dir.glob("*.csv"))
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if RESULT_DIR.exists():
        paths.extend(RESULT_DIR.glob("**/review_samples.csv"))
        paths.extend(RESULT_DIR.glob("**/manual_labels.csv"))
    # 注释：给变量 paths 赋值，供后续步骤使用。
    paths = sorted(set(paths), key=lambda p: p.stat().st_mtime)

    # 注释：给变量 rows 赋值，供后续步骤使用。
    rows = []
    # 注释：循环处理一组数据。
    for path in paths:
        # 注释：尝试执行可能出错的代码。
        try:
            # 注释：给变量 df 赋值，供后续步骤使用。
            df = pd.read_csv(path, encoding="utf-8-sig")
        # 注释：处理 try 中出现的异常。
        except Exception:
            continue
        # 注释：给变量 label_col 赋值，供后续步骤使用。
        label_col = "review_label" if "review_label" in df.columns else "label" if "label" in df.columns else None
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if not label_col or "text" not in df.columns:
            continue
        # 注释：循环处理一组数据。
        for _, row in df.iterrows():
            # 注释：给变量 legacy_feedback_label 赋值，供后续步骤使用。
            legacy_feedback_label = (
                path.name == "review_samples.csv"
                and "label_schema" not in df.columns
                and label_col == "review_label"
            )
            # 注释：给变量 label 赋值，供后续步骤使用。
            label = normalize_label(row.get(label_col), legacy_feedback_label=legacy_feedback_label)
            # 注释：条件判断：满足条件时执行下面缩进的代码。
            if pd.isna(label):
                continue
            rows.append({
                "partition": row.get("partition", "人工反馈"),
                "bvid": row.get("bvid", path.stem),
                "text": row["text"],
                "label": int(label),
            })

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not rows:
        # 注释：返回当前函数的结果。
        return pd.DataFrame(columns=["partition", "bvid", "text", "label"])
    # 注释：给变量 feedback 赋值，供后续步骤使用。
    feedback = pd.DataFrame(rows)
    feedback["text_clean_key"] = feedback["text"].map(clean_text)
    # 注释：给变量 feedback 赋值，供后续步骤使用。
    feedback = feedback[feedback["text_clean_key"].str.len() > 0].copy()
    # 注释：给变量 feedback 赋值，供后续步骤使用。
    feedback = feedback.drop_duplicates(["text_clean_key"], keep="last")
    # 注释：返回当前函数的结果。
    return feedback.drop(columns=["text_clean_key"])


# 注释：获取已经人工标注过的文本集合，避免重复询问。
def get_reviewed_texts(feedback_dir=FEEDBACK_DIR):
    # 注释：给变量 feedback 赋值，供后续步骤使用。
    feedback = load_feedback_data(feedback_dir)
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if feedback.empty:
        # 注释：返回当前函数的结果。
        return set()
    # 注释：返回当前函数的结果。
    return {clean_text(text) for text in feedback["text"].astype(str) if clean_text(text)}


# 注释：绘制学习区和生活区的情感占比柱状图。
def plot_bar(df, path):
    plt.figure(figsize=(7, 4.2))
    # 注释：给变量 pivot 赋值，供后续步骤使用。
    pivot = df.pivot(index="partition", columns="pred_label", values="ratio").fillna(0)
    # 注释：给变量 pivot 赋值，供后续步骤使用。
    pivot = pivot.reindex(columns=["正面", "负面", "中性"], fill_value=0)
    pivot.plot(kind="bar", ax=plt.gca())
    plt.ylabel("占比")
    plt.xlabel("分区")
    plt.title("学习区与生活区弹幕情感占比（三分类）")
    plt.ylim(0, 1)
    plt.xticks(rotation=0)
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


# 注释：绘制不同机器学习模型的 accuracy/F1 对比图。
def plot_metrics(metrics, path):
    plt.figure(figsize=(7, 4.2))
    # 注释：给变量 x 赋值，供后续步骤使用。
    x = np.arange(len(metrics))
    # 注释：给变量 width 赋值，供后续步骤使用。
    width = 0.35
    plt.bar(x - width/2, metrics["accuracy"], width, label="准确率")
    plt.bar(x + width/2, metrics["f1"], width, label="宏平均F1")
    plt.xticks(x, metrics["model"], rotation=0)
    plt.ylim(0, 1)
    plt.ylabel("得分")
    plt.title("机器学习模型性能对比")
    plt.legend()
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


# 注释：绘制最优模型的混淆矩阵。
def plot_confusion_matrix(cm, path):
    plt.figure(figsize=(5.2, 4.6))
    plt.imshow(cm, cmap="Blues")
    plt.title("最优模型混淆矩阵")
    plt.colorbar(fraction=0.046, pad=0.04)
    # 注释：给变量 ticks 赋值，供后续步骤使用。
    ticks = np.arange(len(ORDERED_LABEL_NAMES))
    plt.xticks(ticks, ORDERED_LABEL_NAMES)
    plt.yticks(ticks, ORDERED_LABEL_NAMES)
    plt.xlabel("预测标签")
    plt.ylabel("真实标签")
    # 注释：给变量 threshold 赋值，供后续步骤使用。
    threshold = cm.max() / 2 if cm.size and cm.max() else 0
    # 注释：循环处理一组数据。
    for i in range(cm.shape[0]):
        # 注释：循环处理一组数据。
        for j in range(cm.shape[1]):
            # 注释：给变量 color 赋值，供后续步骤使用。
            color = "white" if cm[i, j] > threshold else "black"
            plt.text(j, i, str(cm[i, j]), ha="center", va="center", color=color)
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


# 注释：统计并绘制弹幕高频词 Top15。
def plot_keywords(df, path):
    # 注释：给变量 texts 赋值，供后续步骤使用。
    texts = "".join(df["text_clean"].astype(str).tolist())
    # 注释：给变量 words 赋值，供后续步骤使用。
    words = tokenize(texts)
    # 注释：给变量 freq 赋值，供后续步骤使用。
    freq = {}
    # 注释：循环处理一组数据。
    for w in words:
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if w in STOP_WORDS or len(w.strip()) == 0:
            continue
        freq[w] = freq.get(w, 0) + 1
    # 注释：给变量 top 赋值，供后续步骤使用。
    top = sorted(freq.items(), key=lambda x: x[1], reverse=True)[:15]
    # 注释：给变量 labels 赋值，供后续步骤使用。
    labels = [i[0] for i in top][::-1]
    # 注释：给变量 values 赋值，供后续步骤使用。
    values = [i[1] for i in top][::-1]
    plt.figure(figsize=(7, 4.2))
    plt.barh(labels, values)
    plt.xlabel("词频")
    plt.title("弹幕高频词 Top15")
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


# 注释：统一拿到模型预测标签、置信度和类别概率。
def predict_with_confidence(model, X):
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if hasattr(model, "predict_proba"):
        # 注释：给变量 proba 赋值，供后续步骤使用。
        proba = model.predict_proba(X)
        # 注释：给变量 index 赋值，供后续步骤使用。
        index = np.argmax(proba, axis=1)
        # 注释：给变量 pred 赋值，供后续步骤使用。
        pred = model.classes_[index]
        # 注释：给变量 confidence 赋值，供后续步骤使用。
        confidence = proba[np.arange(len(index)), index]
        # 注释：返回当前函数的结果。
        return pred, confidence, proba, model.classes_

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if hasattr(model, "decision_function"):
        # 注释：给变量 score 赋值，供后续步骤使用。
        score = model.decision_function(X)
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if score.ndim == 1:
            # 注释：给变量 prob_pos 赋值，供后续步骤使用。
            prob_pos = 1 / (1 + np.exp(-score))
            # 注释：给变量 proba 赋值，供后续步骤使用。
            proba = np.vstack([1 - prob_pos, prob_pos]).T
            # 注释：给变量 classes 赋值，供后续步骤使用。
            classes = model.classes_
            # 注释：给变量 index 赋值，供后续步骤使用。
            index = np.argmax(proba, axis=1)
            # 注释：给变量 pred 赋值，供后续步骤使用。
            pred = classes[index]
            # 注释：给变量 confidence 赋值，供后续步骤使用。
            confidence = np.maximum(prob_pos, 1 - prob_pos)
            # 注释：返回当前函数的结果。
            return pred, confidence, proba, classes

        # 注释：给变量 exp_score 赋值，供后续步骤使用。
        exp_score = np.exp(score - score.max(axis=1, keepdims=True))
        # 注释：给变量 proba 赋值，供后续步骤使用。
        proba = exp_score / exp_score.sum(axis=1, keepdims=True)
        # 注释：给变量 index 赋值，供后续步骤使用。
        index = np.argmax(proba, axis=1)
        # 注释：给变量 pred 赋值，供后续步骤使用。
        pred = model.classes_[index]
        # 注释：给变量 confidence 赋值，供后续步骤使用。
        confidence = proba[np.arange(len(index)), index]
        # 注释：返回当前函数的结果。
        return pred, confidence, proba, model.classes_

    # 注释：给变量 pred 赋值，供后续步骤使用。
    pred = model.predict(X)
    # 注释：给变量 confidence 赋值，供后续步骤使用。
    confidence = np.ones(len(pred))
    # 注释：给变量 proba 赋值，供后续步骤使用。
    proba = np.ones((len(pred), 1))
    # 注释：返回当前函数的结果。
    return pred, confidence, proba, np.array([pred[0]]) if len(pred) else np.array([])


# 注释：把概率矩阵拆成 prob_negative/prob_neutral/prob_positive 三列。
def add_class_probabilities(df, proba, classes):
    # 注释：给变量 class_to_column 赋值，供后续步骤使用。
    class_to_column = {-1: "prob_negative", 0: "prob_neutral", 1: "prob_positive"}
    # 注释：循环处理一组数据。
    for column in class_to_column.values():
        df[column] = 0.0
    # 注释：循环处理一组数据。
    for idx, cls in enumerate(classes):
        # 注释：给变量 column 赋值，供后续步骤使用。
        column = class_to_column.get(int(cls))
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if column:
            df[column] = proba[:, idx]
    # 注释：返回当前函数的结果。
    return df


# 注释：综合模型概率、词典分数和规则，生成最终展示标签。
def assign_display_label(row):
    # 注释：给变量 score 赋值，供后续步骤使用。
    score = row["lexicon_score"]
    # 注释：给变量 positive_prob 赋值，供后续步骤使用。
    positive_prob = row.get("prob_positive", 0.0)
    # 注释：给变量 negative_prob 赋值，供后续步骤使用。
    negative_prob = row.get("prob_negative", 0.0)
    # 注释：给变量 neutral_prob 赋值，供后续步骤使用。
    neutral_prob = row.get("prob_neutral", 0.0)
    # 注释：给变量 best_polar_prob 赋值，供后续步骤使用。
    best_polar_prob = max(positive_prob, negative_prob)
    # 注释：给变量 lexicon_abs 赋值，供后续步骤使用。
    lexicon_abs = row.get("lexicon_abs_score", 0.0)
    # 注释：给变量 raw_label 赋值，供后续步骤使用。
    raw_label = row.get("pred_raw_label", "")
    # 注释：给变量 has_neutral_cue 赋值，供后续步骤使用。
    has_neutral_cue = contains_neutral_cue(row.get("text_clean", ""))

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if has_obvious_positive_cue(row):
        # 注释：返回当前函数的结果。
        return "正面"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if has_obvious_negative_cue(row):
        # 注释：返回当前函数的结果。
        return "负面"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if positive_prob >= MODEL_STRONG_THRESHOLD and negative_prob < 0.2:
        # 注释：返回当前函数的结果。
        return "正面"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if negative_prob >= MODEL_STRONG_THRESHOLD and positive_prob < 0.2:
        # 注释：返回当前函数的结果。
        return "负面"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if should_keep_neutral(row):
        # 注释：返回当前函数的结果。
        return "中性"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if score >= 2 or (score >= LEXICON_STRONG_THRESHOLD and positive_prob >= 0.45 and positive_prob >= neutral_prob):
        # 注释：返回当前函数的结果。
        return "正面"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if score <= -2 or (score <= -LEXICON_STRONG_THRESHOLD and negative_prob >= 0.45 and negative_prob >= neutral_prob):
        # 注释：返回当前函数的结果。
        return "负面"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if neutral_prob >= NEUTRAL_STRICT_THRESHOLD and best_polar_prob < 0.35:
        # 注释：返回当前函数的结果。
        return "中性"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if (
        neutral_prob >= 0.55
        and best_polar_prob < 0.45
        and has_neutral_cue
        and lexicon_abs <= 1
    ):
        # 注释：返回当前函数的结果。
        return "中性"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if raw_label == "中性" and lexicon_abs == 0 and neutral_prob >= 0.35:
        # 注释：返回当前函数的结果。
        return "中性"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if lexicon_abs == 0 and neutral_prob >= 0.30 and abs(positive_prob - negative_prob) < 0.08:
        # 注释：返回当前函数的结果。
        return "中性"

    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if lexicon_abs > 0:
        # 注释：返回当前函数的结果。
        return "正面" if score > 0 else "负面"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if positive_prob >= negative_prob:
        # 注释：返回当前函数的结果。
        return "正面"
    # 注释：返回当前函数的结果。
    return "负面"


# 注释：说明样本为什么进入人工复核池。
def review_reason(row):
    # 注释：给变量 score 赋值，供后续步骤使用。
    score = row["lexicon_score"]
    # 注释：给变量 raw 赋值，供后续步骤使用。
    raw = row["pred_raw_label"]
    # 注释：给变量 confidence 赋值，供后续步骤使用。
    confidence = row["model_confidence"]
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if confidence < MODEL_CONFIDENCE_THRESHOLD:
        # 注释：返回当前函数的结果。
        return "模型低置信度"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if score >= LEXICON_STRONG_THRESHOLD and raw == "负面":
        # 注释：返回当前函数的结果。
        return "词典偏正但模型偏负"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if score <= -LEXICON_STRONG_THRESHOLD and raw == "正面":
        # 注释：返回当前函数的结果。
        return "词典偏负但模型偏正"
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if row["pred_label"] == "中性" and row["lexicon_abs_score"] > 0:
        # 注释：返回当前函数的结果。
        return "中性结果含情感词"
    # 注释：返回当前函数的结果。
    return "代表样本"


# 注释：抽取低置信或冲突样本，生成 review_samples.csv。
def create_review_samples(df, path, review_ratio=REVIEW_SAMPLE_RATIO, reviewed_texts=None):
    # 注释：给变量 columns 赋值，供后续步骤使用。
    columns = [
        "review_label", "label_schema", "review_reason", "partition", "bvid", "text",
        "pred_label", "pred_raw_label", "model_confidence", "lexicon_score",
        "prob_positive", "prob_neutral", "prob_negative",
        "pos_cnt", "neg_cnt", "word_len",
    ]
    # 注释：给变量 review_df 赋值，供后续步骤使用。
    review_df = df.copy()
    # 注释：给变量 reviewed_clean_texts 赋值，供后续步骤使用。
    reviewed_clean_texts = {clean_text(text) for text in (reviewed_texts or set()) if clean_text(text)}
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if reviewed_clean_texts:
        # 注释：给变量 review_df 赋值，供后续步骤使用。
        review_df = review_df[~review_df["text_clean"].astype(str).isin(reviewed_clean_texts)].copy()
    # 注释：给变量 review_df 赋值，供后续步骤使用。
    review_df = review_df.drop_duplicates(["text_clean"]).copy()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not review_df.empty:
        # 注释：给变量 obvious_mask 赋值，供后续步骤使用。
        obvious_mask = review_df.apply(is_obvious_auto_label, axis=1)
        # 注释：给变量 review_df 赋值，供后续步骤使用。
        review_df = review_df[~obvious_mask].copy()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if review_df.empty:
        # 注释：给变量 empty 赋值，供后续步骤使用。
        empty = pd.DataFrame(columns=columns)
        # 注释：把 DataFrame 保存为 CSV 文件。
        empty.to_csv(path, index=False, encoding="utf-8-sig")
        # 注释：返回当前函数的结果。
        return path, 0, review_ratio

    # 注释：给变量 target_count 赋值，供后续步骤使用。
    target_count = min(MAX_REVIEW_SAMPLE_COUNT, max(1, int(np.ceil(len(review_df) * review_ratio))))
    review_df["review_reason"] = review_df.apply(review_reason, axis=1)
    review_df["sort_score"] = (
        (1 - review_df["model_confidence"].clip(0, 1)) * 3
        + review_df["lexicon_abs_score"].clip(0, 3)
        + (review_df["review_reason"] != "代表样本").astype(int)
    )

    # 注释：给变量 parts 赋值，供后续步骤使用。
    parts = []
    priority = review_df[review_df["review_reason"] != "代表样本"].sort_values("sort_score", ascending=False)
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not priority.empty:
        parts.append(priority.head(target_count))
    # 注释：循环处理一组数据。
    for label in ["正面", "负面", "中性"]:
        # 注释：给变量 subset 赋值，供后续步骤使用。
        subset = review_df[
            (review_df["pred_label"] == label)
            & (review_df["model_confidence"] < MODEL_CONFIDENCE_THRESHOLD)
        ].sort_values("sort_score", ascending=False)
        # 注释：条件判断：满足条件时执行下面缩进的代码。
        if not subset.empty:
            parts.append(subset.head(max(1, int(target_count * 0.1))))
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if parts:
        # 注释：给变量 sampled 赋值，供后续步骤使用。
        sampled = pd.concat(parts).drop_duplicates(["partition", "bvid", "text_clean"])
    # 注释：兜底分支。
    else:
        # 注释：给变量 sampled 赋值，供后续步骤使用。
        sampled = review_df[review_df["model_confidence"] < MODEL_CONFIDENCE_THRESHOLD].sort_values("sort_score", ascending=False)
    # 注释：给变量 sampled 赋值，供后续步骤使用。
    sampled = sampled.head(target_count)

    # 注释：给变量 sampled 赋值，供后续步骤使用。
    sampled = sampled.copy()
    sampled.insert(0, "review_label", "")
    sampled.insert(1, "label_schema", "1=正面,0=中性,-1=负面")
    # 注释：把 DataFrame 保存为 CSV 文件。
    sampled[columns].to_csv(path, index=False, encoding="utf-8-sig")
    # 注释：返回当前函数的结果。
    return path, len(sampled), review_ratio


# 注释：按正面、负面、中性分别导出弹幕 CSV。
def export_label_groups(df, result_dir):
    # 注释：给变量 export_columns 赋值，供后续步骤使用。
    export_columns = [
        "partition", "bvid", "text", "pred_label", "pred_raw_label",
        "model_confidence", "prob_positive", "prob_neutral", "prob_negative",
        "lexicon_score", "pos_cnt", "neg_cnt", "manual_override", "manual_label",
    ]
    # 注释：给变量 export_columns 赋值，供后续步骤使用。
    export_columns = [column for column in export_columns if column in df.columns]
    # 注释：给变量 label_files 赋值，供后续步骤使用。
    label_files = {
        "正面": "positive_comments.csv",
        "负面": "negative_comments.csv",
        "中性": "neutral_comments.csv",
    }
    # 注释：给变量 paths 赋值，供后续步骤使用。
    paths = {}
    # 注释：循环处理一组数据。
    for label, filename in label_files.items():
        subset = df[df["pred_label"] == label].copy()
        # 注释：把 DataFrame 保存为 CSV 文件。
        subset[export_columns].to_csv(result_dir / filename, index=False, encoding="utf-8-sig")
        paths[label] = result_dir / filename
    # 注释：返回当前函数的结果。
    return paths


# 注释：导出低置信、冲突、视频维度统计等诊断文件。
def export_diagnostics(df, result_dir):
    # 注释：给变量 confidence_summary 赋值，供后续步骤使用。
    confidence_summary = (
        # 注释：按字段分组统计。
        df.groupby(["partition", "pred_label"])
        .agg(
            # 注释：给变量 count 赋值，供后续步骤使用。
            count=("text", "size"),
            # 注释：给变量 mean_confidence 赋值，供后续步骤使用。
            mean_confidence=("model_confidence", "mean"),
            # 注释：给变量 mean_positive_prob 赋值，供后续步骤使用。
            mean_positive_prob=("prob_positive", "mean"),
            # 注释：给变量 mean_neutral_prob 赋值，供后续步骤使用。
            mean_neutral_prob=("prob_neutral", "mean"),
            # 注释：给变量 mean_negative_prob 赋值，供后续步骤使用。
            mean_negative_prob=("prob_negative", "mean"),
            # 注释：给变量 mean_lexicon_score 赋值，供后续步骤使用。
            mean_lexicon_score=("lexicon_score", "mean"),
        )
        .reset_index()
    )
    # 注释：把 DataFrame 保存为 CSV 文件。
    confidence_summary.to_csv(result_dir / "confidence_summary.csv", index=False, encoding="utf-8-sig")

    # 注释：给变量 video_stat 赋值，供后续步骤使用。
    video_stat = df.groupby(["partition", "bvid", "pred_label"]).size().reset_index(name="count")
    # 注释：给变量 video_total 赋值，供后续步骤使用。
    video_total = df.groupby(["partition", "bvid"]).size().reset_index(name="total")
    # 注释：给变量 video_stat 赋值，供后续步骤使用。
    video_stat = video_stat.merge(video_total, on=["partition", "bvid"])
    video_stat["ratio"] = video_stat["count"] / video_stat["total"]
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if "title" in df.columns:
        # 注释：给变量 title_map 赋值，供后续步骤使用。
        title_map = df.groupby(["partition", "bvid"])["title"].first().reset_index()
        # 注释：给变量 video_stat 赋值，供后续步骤使用。
        video_stat = video_stat.merge(title_map, on=["partition", "bvid"], how="left")
        # 注释：给变量 cols 赋值，供后续步骤使用。
        cols = ["partition", "bvid", "title", "pred_label", "count", "total", "ratio"]
        # 注释：给变量 video_stat 赋值，供后续步骤使用。
        video_stat = video_stat[cols]
    # 注释：把 DataFrame 保存为 CSV 文件。
    video_stat.to_csv(result_dir / "video_sentiment_stats.csv", index=False, encoding="utf-8-sig")

    # 注释：给变量 low_n 赋值，供后续步骤使用。
    low_n = max(1, int(np.ceil(len(df) * REVIEW_SAMPLE_RATIO)))
    # 注释：给变量 low_conf 赋值，供后续步骤使用。
    low_conf = df.sort_values("model_confidence", ascending=True).head(low_n)
    # 注释：把 DataFrame 保存为 CSV 文件。
    low_conf.to_csv(result_dir / "low_confidence_samples.csv", index=False, encoding="utf-8-sig")

    # 注释：给变量 conflict 赋值，供后续步骤使用。
    conflict = df[
        ((df["lexicon_score"] >= LEXICON_STRONG_THRESHOLD) & (df["pred_raw_label"] == "负面"))
        | ((df["lexicon_score"] <= -LEXICON_STRONG_THRESHOLD) & (df["pred_raw_label"] == "正面"))
        | ((df["pred_label"] == "中性") & (df["lexicon_abs_score"] > 0))
    ].copy()
    # 注释：把 DataFrame 保存为 CSV 文件。
    conflict.to_csv(result_dir / "conflict_samples.csv", index=False, encoding="utf-8-sig")

    # 注释：返回当前函数的结果。
    return {
        "confidence_summary": result_dir / "confidence_summary.csv",
        "video_sentiment_stats": result_dir / "video_sentiment_stats.csv",
        "low_confidence_samples": result_dir / "low_confidence_samples.csv",
        "conflict_samples": result_dir / "conflict_samples.csv",
        "low_confidence_count": len(low_conf),
        "conflict_count": len(conflict),
    }


# 注释：把当前轮分区统计和上一轮结果做对比。
def save_iteration_comparison(current_stat, result_dir):
    # 注释：给变量 candidates 赋值，供后续步骤使用。
    candidates = []
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if RESULT_DIR.exists():
        # 注释：循环处理一组数据。
        for path in RESULT_DIR.glob("**/partition_sentiment_stats.csv"):
            # 注释：条件判断：满足条件时执行下面缩进的代码。
            if path.parent.resolve() == result_dir.resolve():
                continue
            candidates.append(path)
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not candidates:
        # 注释：返回当前函数的结果。
        return None
    # 注释：给变量 previous_path 赋值，供后续步骤使用。
    previous_path = max(candidates, key=lambda p: p.stat().st_mtime)
    # 注释：给变量 previous 赋值，供后续步骤使用。
    previous = pd.read_csv(previous_path, encoding="utf-8-sig")
    # 注释：给变量 merged 赋值，供后续步骤使用。
    merged = current_stat.merge(
        previous[["partition", "pred_label", "ratio"]].rename(columns={"ratio": "previous_ratio"}),
        # 注释：给变量 on 赋值，供后续步骤使用。
        on=["partition", "pred_label"],
        # 注释：给变量 how 赋值，供后续步骤使用。
        how="outer",
    )
    merged["ratio"] = merged["ratio"].fillna(0)
    merged["previous_ratio"] = merged["previous_ratio"].fillna(0)
    merged["delta_ratio"] = merged["ratio"] - merged["previous_ratio"]
    merged["previous_experiment"] = previous_path.parent.name
    # 注释：给变量 out 赋值，供后续步骤使用。
    out = result_dir / "iteration_comparison.csv"
    # 注释：把 DataFrame 保存为 CSV 文件。
    merged.to_csv(out, index=False, encoding="utf-8-sig")
    # 注释：返回当前函数的结果。
    return out


# 注释：生成 Markdown 格式的自动实验摘要。
def write_analysis_summary(path, summary_data):
    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = summary_data["stat"].copy()
    # 注释：给变量 metrics 赋值，供后续步骤使用。
    metrics = summary_data["metrics"].copy()
    # 注释：给变量 best_row 赋值，供后续步骤使用。
    best_row = metrics.iloc[0]
    # 注释：给变量 lines 赋值，供后续步骤使用。
    lines = [
        "# B站弹幕情感分析实验摘要",
        "",
        f"- 最优模型：{summary_data['best_model']}",
        f"- 最优模型准确率：{best_row['accuracy']:.4f}",
        f"- 最优模型宏平均F1：{best_row['f1']:.4f}",
        f"- 训练样本数：{summary_data['train_count']}",
        f"- 历史人工反馈样本数：{summary_data['feedback_count']}",
        f"- 本轮待复核样本数：{summary_data['review_count']}（{summary_data['review_ratio']:.0%}）",
        f"- 文本特征：jieba词级TF-IDF + 字级2-4gram TF-IDF + 情感词典特征",
        f"- 低置信样本数：{summary_data['diagnostics']['low_confidence_count']}",
        f"- 词典-模型冲突样本数：{summary_data['diagnostics']['conflict_count']}",
        "",
        "## 分区情感比例",
        "",
    ]
    # 注释：循环处理一组数据。
    for _, row in stat.sort_values(["partition", "pred_label"]).iterrows():
        lines.append(f"- {row['partition']} {row['pred_label']}：{row['ratio']:.2%}（{int(row['count'])}/{int(row['total'])}）")
    lines.extend([
        "",
        "## 建议",
        "",
        "- 优先标注 `review_samples.csv`，它已经按低置信度和冲突程度抽取约8%。",
        "- 如果某类明显偏多，先抽查对应的 `positive_comments.csv`、`negative_comments.csv`、`neutral_comments.csv`。",
        "- 跑 2-3 轮后，使用最后一轮的 `partition_sentiment_stats.csv` 和图表作为汇报依据。",
    ])
    path.write_text("\n".join(lines), encoding="utf-8")
    # 注释：返回当前函数的结果。
    return path


# 注释：完整分析流程：训练、评估、预测、导出结果和图表。
def analyze(
    # 注释：给变量 train_data_path 赋值，供后续步骤使用。
    train_data_path=TRAIN_DATA_PATH,
    # 注释：给变量 predict_data_path 赋值，供后续步骤使用。
    predict_data_path=None,
    # 注释：给变量 result_dir 赋值，供后续步骤使用。
    result_dir=RESULT_DIR,
    # 注释：给变量 fig_dir 赋值，供后续步骤使用。
    fig_dir=FIG_DIR,
    # 注释：给变量 feedback_dir 赋值，供后续步骤使用。
    feedback_dir=FEEDBACK_DIR,
):
    # 注释：给变量 train_data_path 赋值，供后续步骤使用。
    train_data_path = Path(train_data_path)
    # 注释：给变量 result_dir 赋值，供后续步骤使用。
    result_dir = Path(result_dir)
    # 注释：给变量 fig_dir 赋值，供后续步骤使用。
    fig_dir = Path(fig_dir)
    result_dir.mkdir(parents=True, exist_ok=True)
    fig_dir.mkdir(parents=True, exist_ok=True)

    setup_chinese_font()

    # 注释：给变量 train_df 赋值，供后续步骤使用。
    train_df = load_and_prepare(train_data_path)
    # 注释：给变量 neutral_seed_df 赋值，供后续步骤使用。
    neutral_seed_df = prepare_dataframe(make_neutral_seed_df())
    # 注释：给变量 feedback_raw 赋值，供后续步骤使用。
    feedback_raw = load_feedback_data(feedback_dir)
    # 注释：给变量 feedback_df 赋值，供后续步骤使用。
    feedback_df = prepare_dataframe(feedback_raw) if not feedback_raw.empty else feedback_raw
    # 注释：给变量 train_parts 赋值，供后续步骤使用。
    train_parts = [train_df, neutral_seed_df]
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not feedback_df.empty:
        train_parts.append(feedback_df)
    # 注释：给变量 train_df 赋值，供后续步骤使用。
    train_df = pd.concat(train_parts, ignore_index=True).drop_duplicates(["text_clean"], keep="last")
    # 注释：给变量 feedback_label_map 赋值，供后续步骤使用。
    feedback_label_map = {}
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if not feedback_df.empty:
        # 注释：给变量 feedback_label_map 赋值，供后续步骤使用。
        feedback_label_map = (
            feedback_df[feedback_df["label"].notna()]
            .drop_duplicates(["text_clean"], keep="last")
            .set_index("text_clean")["label"]
            .astype(int)
            .to_dict()
        )

    # 注释：给变量 predict_path 赋值，供后续步骤使用。
    predict_path = Path(predict_data_path) if predict_data_path else RAW_DATA_PATH if RAW_DATA_PATH.exists() else train_data_path
    # 注释：给变量 predict_df 赋值，供后续步骤使用。
    predict_df = load_and_prepare(predict_path)

    # 注释：给变量 labeled 赋值，供后续步骤使用。
    labeled = train_df[train_df["label"].notna()].copy()
    # 注释：给变量 y 赋值，供后续步骤使用。
    y = labeled["label"].astype(int)
    # 注释：给变量 word_vectorizer 赋值，供后续步骤使用。
    word_vectorizer = TfidfVectorizer(
        # 注释：给变量 tokenizer 赋值，供后续步骤使用。
        tokenizer=tokenize,
        # 注释：给变量 token_pattern 赋值，供后续步骤使用。
        token_pattern=None,
        # 注释：给变量 max_features 赋值，供后续步骤使用。
        max_features=WORD_TFIDF_MAX_FEATURES,
        # 注释：给变量 ngram_range 赋值，供后续步骤使用。
        ngram_range=(1, 2),
        # 注释：给变量 sublinear_tf 赋值，供后续步骤使用。
        sublinear_tf=True,
    )
    # 注释：给变量 char_vectorizer 赋值，供后续步骤使用。
    char_vectorizer = TfidfVectorizer(
        # 注释：给变量 analyzer 赋值，供后续步骤使用。
        analyzer="char",
        # 注释：给变量 max_features 赋值，供后续步骤使用。
        max_features=CHAR_TFIDF_MAX_FEATURES,
        # 注释：给变量 ngram_range 赋值，供后续步骤使用。
        ngram_range=(2, 4),
        # 注释：给变量 sublinear_tf 赋值，供后续步骤使用。
        sublinear_tf=True,
    )
    # 注释：给变量 X_word 赋值，供后续步骤使用。
    X_word = word_vectorizer.fit_transform(labeled["text_clean"])
    # 注释：给变量 X_char 赋值，供后续步骤使用。
    X_char = char_vectorizer.fit_transform(labeled["text_clean"])
    # 注释：给变量 X_extra 赋值，供后续步骤使用。
    X_extra = csr_matrix(labeled[FEATURE_COLUMNS].values)
    # 注释：给变量 X 赋值，供后续步骤使用。
    X = hstack([X_word, X_char, X_extra])

    # 注释：给变量 class_counts 赋值，供后续步骤使用。
    class_counts = y.value_counts()
    stratify = y if len(class_counts) > 1 and class_counts.min() >= 2 else None
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=stratify)
    # 注释：给变量 models 赋值，供后续步骤使用。
    models = {
        # 注释：创建一个机器学习分类模型。
        "朴素贝叶斯": MultinomialNB(),
        # 注释：创建一个机器学习分类模型。
        "逻辑回归": LogisticRegression(max_iter=1000, class_weight="balanced"),
        # 注释：创建一个机器学习分类模型。
        "SVM": LinearSVC(max_iter=5000, class_weight="balanced"),
        # 注释：创建一个机器学习分类模型。
        "随机森林": RandomForestClassifier(n_estimators=160, random_state=42, class_weight="balanced_subsample"),
    }

    # 注释：给变量 rows 赋值，供后续步骤使用。
    rows = []
    # 注释：给变量 trained 赋值，供后续步骤使用。
    trained = {}
    # 注释：给变量 test_predictions 赋值，供后续步骤使用。
    test_predictions = {}
    # 注释：循环处理一组数据。
    for name, model in models.items():
        # 注释：训练模型或特征提取器。
        model.fit(X_train, y_train)
        # 注释：给变量 pred 赋值，供后续步骤使用。
        pred = model.predict(X_test)
        rows.append({
            "model": name,
            "accuracy": accuracy_score(y_test, pred),
            "f1": f1_score(y_test, pred, average="macro", zero_division=0),
        })
        trained[name] = model
        test_predictions[name] = pred
    # 注释：给变量 metrics 赋值，供后续步骤使用。
    metrics = pd.DataFrame(rows).sort_values("f1", ascending=False)
    # 注释：把 DataFrame 保存为 CSV 文件。
    metrics.to_csv(result_dir / "model_metrics.csv", index=False, encoding="utf-8-sig")
    plot_metrics(metrics, fig_dir / "model_metrics.png")

    # 注释：给变量 best_name 赋值，供后续步骤使用。
    best_name = metrics.iloc[0]["model"]
    # 注释：给变量 best_model 赋值，供后续步骤使用。
    best_model = trained[best_name]
    # 注释：给变量 best_test_pred 赋值，供后续步骤使用。
    best_test_pred = test_predictions[best_name]
    # 注释：给变量 report 赋值，供后续步骤使用。
    report = classification_report(
        y_test,
        best_test_pred,
        # 注释：给变量 labels 赋值，供后续步骤使用。
        labels=ORDERED_LABELS,
        # 注释：给变量 target_names 赋值，供后续步骤使用。
        target_names=ORDERED_LABEL_NAMES,
        # 注释：给变量 output_dict 赋值，供后续步骤使用。
        output_dict=True,
        # 注释：给变量 zero_division 赋值，供后续步骤使用。
        zero_division=0,
    )
    # 注释：把 DataFrame 保存为 CSV 文件。
    pd.DataFrame(report).transpose().to_csv(result_dir / "classification_report_full.csv", encoding="utf-8-sig")
    # 注释：给变量 cm 赋值，供后续步骤使用。
    cm = confusion_matrix(y_test, best_test_pred, labels=ORDERED_LABELS)
    # 注释：把 DataFrame 保存为 CSV 文件。
    pd.DataFrame(cm, index=ORDERED_LABEL_NAMES, columns=ORDERED_LABEL_NAMES).to_csv(
        result_dir / "confusion_matrix.csv",
        # 注释：给变量 encoding 赋值，供后续步骤使用。
        encoding="utf-8-sig",
    )
    plot_confusion_matrix(cm, fig_dir / "confusion_matrix.png")

    # 注释：给变量 X_all 赋值，供后续步骤使用。
    X_all = hstack([
        word_vectorizer.transform(predict_df["text_clean"]),
        char_vectorizer.transform(predict_df["text_clean"]),
        csr_matrix(predict_df[FEATURE_COLUMNS].values)
    ])
    pred, confidence, proba, classes = predict_with_confidence(best_model, X_all)
    predict_df["pred"] = pred
    predict_df["model_confidence"] = confidence
    # 注释：给变量 predict_df 赋值，供后续步骤使用。
    predict_df = add_class_probabilities(predict_df, proba, classes)
    predict_df["pred_raw_label"] = predict_df["pred"].map(LABEL_NAMES)
    predict_df["pred_label"] = predict_df.apply(assign_display_label, axis=1)
    predict_df["manual_label"] = predict_df["text_clean"].map(feedback_label_map)
    predict_df["manual_override"] = predict_df["manual_label"].notna()
    # 注释：条件判断：满足条件时执行下面缩进的代码。
    if predict_df["manual_override"].any():
        # 注释：给变量 manual_labels 赋值，供后续步骤使用。
        manual_labels = predict_df.loc[predict_df["manual_override"], "manual_label"].astype(int)
        predict_df.loc[predict_df["manual_override"], "pred_label"] = manual_labels.map(LABEL_NAMES)
    # 注释：把 DataFrame 保存为 CSV 文件。
    predict_df.to_csv(result_dir / "danmu_predicted.csv", index=False, encoding="utf-8-sig")
    # 注释：给变量 label_group_paths 赋值，供后续步骤使用。
    label_group_paths = export_label_groups(predict_df, result_dir)
    # 注释：给变量 diagnostics 赋值，供后续步骤使用。
    diagnostics = export_diagnostics(predict_df, result_dir)

    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = predict_df.groupby(["partition", "pred_label"]).size().reset_index(name="count")
    # 注释：给变量 total 赋值，供后续步骤使用。
    total = predict_df.groupby("partition").size().reset_index(name="total")
    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = stat.merge(total, on="partition")
    stat["ratio"] = stat["count"] / stat["total"]
    # 注释：把 DataFrame 保存为 CSV 文件。
    stat.to_csv(result_dir / "partition_sentiment_stats.csv", index=False, encoding="utf-8-sig")
    # 注释：给变量 iteration_comparison_path 赋值，供后续步骤使用。
    iteration_comparison_path = save_iteration_comparison(stat, result_dir)
    plot_bar(stat, fig_dir / "partition_sentiment.png")
    plot_keywords(predict_df, fig_dir / "keywords_top15.png")
    # 注释：给变量 reviewed_texts 赋值，供后续步骤使用。
    reviewed_texts = set(feedback_df["text_clean"].astype(str)) if not feedback_df.empty else set()
    review_path, review_count, review_ratio = create_review_samples(
        predict_df,
        result_dir / "review_samples.csv",
        # 注释：给变量 reviewed_texts 赋值，供后续步骤使用。
        reviewed_texts=reviewed_texts,
    )

    with open(result_dir / "classification_report.txt", "w", encoding="utf-8") as f:
        f.write(f"最优模型：{best_name}\n")
        f.write(f"训练数据：{train_data_path.name}\n")
        f.write(f"预测数据：{predict_path.name}\n")
        f.write(f"训练样本数：{len(labeled)}，人工反馈样本数：{len(feedback_df)}，中性种子样本数：{len(neutral_seed_df)}\n")
        f.write(f"本轮待人工复核样本数：{review_count}，抽样比例：{review_ratio:.0%}\n")
        f.write(f"正面词数：{len(POS_WORDS)}，负面词数：{len(NEG_WORDS)}\n")
        f.write(
            "说明：参考中文文本分类实验的字级建模与FastText n-gram思想，"
            "使用 jieba 词级TF-IDF、字级2-4gram TF-IDF、情感词典计数/分数特征；"
            "模型支持正面、负面、中性三分类，并会读取历史人工纠错样本继续学习。\n"
        )
        f.write("最终判定采用保守中性策略：只有中性概率很高且正负概率都弱时才输出中性，否则在正负情绪中择优。\n")
        f.write(metrics.to_string(index=False))

    # 注释：给变量 summary 赋值，供后续步骤使用。
    summary = {
        "best_model": best_name,
        "metrics": metrics,
        "stat": stat,
        "train_data_path": train_data_path,
        "predict_path": predict_path,
        "result_dir": result_dir,
        "fig_dir": fig_dir,
        "review_path": review_path,
        "review_count": review_count,
        "review_ratio": review_ratio,
        "label_group_paths": label_group_paths,
        "diagnostics": diagnostics,
        "iteration_comparison_path": iteration_comparison_path,
        "feedback_count": len(feedback_df),
        "neutral_seed_count": len(neutral_seed_df),
        "train_count": len(labeled),
    }
    summary["analysis_summary_path"] = write_analysis_summary(result_dir / "analysis_summary.md", summary)
    # 注释：返回当前函数的结果。
    return summary


# 注释：单独运行 train_analyze.py 时的入口。
def main():
    # 注释：给变量 summary 赋值，供后续步骤使用。
    summary = analyze()
    print(f"完成。训练数据：{summary['train_data_path'].name}，预测数据：{summary['predict_path'].name}")
    print("结果保存在 results/ 和 figures/。")
    # 注释：给变量 metrics 赋值，供后续步骤使用。
    metrics = summary["metrics"]
    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = summary["stat"]
    print(metrics)
    print(stat)


# 注释：条件判断：满足条件时执行下面缩进的代码。
if __name__ == "__main__":
    main()
