"""
B站学习区/生活区弹幕情感对比分析主程序。
功能：清洗、分词、词典情感特征、TF-IDF、四类机器学习模型训练、全量预测、可视化。
运行：python src/train_analyze.py
"""
import re
from pathlib import Path

import matplotlib
import numpy as np
import pandas as pd

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib import font_manager
from scipy.sparse import hstack, csr_matrix
from sklearn.ensemble import RandomForestClassifier
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, f1_score, classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB
from sklearn.svm import LinearSVC

ROOT = Path(__file__).resolve().parents[1]
TRAIN_DATA_PATH = ROOT / "data" / "danmu_sample_5000.csv"
RAW_DATA_PATH = ROOT / "data" / "raw_bilibili_danmu.csv"
LEXICON_DIR = ROOT / "data" / "sentiment_lexicon"
FEEDBACK_DIR = ROOT / "data" / "feedback"
RESULT_DIR = ROOT / "results"
FIG_DIR = ROOT / "figures"
RESULT_DIR.mkdir(exist_ok=True)
FIG_DIR.mkdir(exist_ok=True)

try:
    import jieba
    def tokenize(text: str):
        return [w for w in jieba.lcut(text) if w.strip()]
except Exception:
    # 无 jieba 环境下的降级方案：中文按字/英文按词切分，保证程序可运行。
    def tokenize(text: str):
        return re.findall(r"[\u4e00-\u9fa5]|[A-Za-z0-9]+", str(text))

# 这里不是完整 HowNet/知网词典，只是程序内置的兜底小词表。
# 完整正负词典会在 load_sentiment_words() 中从 data/sentiment_lexicon/*.txt 自动读取并合并。
DEFAULT_POS_WORDS = set("""
懂了 清楚 有用 喜欢 厉害 高效 开心 治愈 放松 好看 赞 支持 学会 收获 真实 温暖 快乐
牛 绝了 牛逼 太强 好棒 可爱 爱了 宝藏 感动 泪目 笑死 哈哈 舒服 优秀 精彩 认真
靠谱 方便 简单 明白 详细 到位 完整 经典 推荐 收藏 三连 感谢 谢谢 666 nb yyds
""".split())
DEFAULT_NEG_WORDS = set("""
难 焦虑 崩溃 听不懂 烦 压力 困 想哭 无语 枯燥 累 失败 迷茫 拖延 痛苦 没用
烂 差 尬 假 恶心 难受 下头 失望 生气 吵 乱 崩 坏 无聊 看不下去 水 标题党
离谱 破防 问题 错误 垃圾 拉胯 折磨 麻烦 讨厌 别扭
""".split())
STOP_WORDS = set("的 了 啊 呀 呢 吗 吧 和 是 我 你 他 她 它 这 那 一个 一下 真的 有点".split())
NEGATION_WORDS = set("不 没 无 非 未 别 莫 否 不是 没有 无法 不会 不想 不要 别再".split())
DEGREE_WORDS = {
    "极其": 2.2, "超级": 2.0, "非常": 2.0, "特别": 1.8, "太": 1.8,
    "很": 1.5, "真": 1.4, "挺": 1.3, "比较": 1.2, "有点": 0.8, "稍微": 0.7,
}
SENTIMENT_COLUMNS = [
    "pos_cnt", "neg_cnt", "word_len", "exclaim_cnt", "question_cnt",
    "lexicon_score", "lexicon_pos_score", "lexicon_neg_score", "lexicon_abs_score", "sentiment_density",
]
FEATURE_COLUMNS = [
    "pos_cnt", "neg_cnt", "word_len", "exclaim_cnt", "question_cnt",
    "lexicon_pos_score", "lexicon_neg_score", "lexicon_abs_score", "sentiment_density",
]
WORD_TFIDF_MAX_FEATURES = 1500
CHAR_TFIDF_MAX_FEATURES = 2500
LEXICON_STRONG_THRESHOLD = 1.0
MODEL_CONFIDENCE_THRESHOLD = 0.66
NEUTRAL_CONFIDENCE_THRESHOLD = 0.6
NEUTRAL_STRICT_THRESHOLD = 0.75
NEUTRAL_SHORT_TEXT_THRESHOLD = 0.68
MODEL_STRONG_THRESHOLD = 0.85
REVIEW_SAMPLE_RATIO = 0.08
MAX_REVIEW_SAMPLE_COUNT = 100
LABEL_NAMES = {-1: "负面", 0: "中性", 1: "正面"}
ORDERED_LABELS = [-1, 0, 1]
ORDERED_LABEL_NAMES = [LABEL_NAMES[i] for i in ORDERED_LABELS]
LABEL_VALUES = {
    "-1": -1, "负": -1, "负面": -1, "消极": -1, "negative": -1, "neg": -1,
    "1": 1, "正": 1, "正面": 1, "积极": 1, "positive": 1, "pos": 1,
    "0": 0, "中": 0, "中性": 0, "无情绪": 0, "neutral": 0, "neu": 0,
    # 兼容旧版 2=中性 的历史人工标注。
    "2": 0,
}
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
NEUTRAL_CUE_WORDS = set("打卡 来了 前排 第一 报到 到此一游 路过 签到 考古 插眼 马克 收藏 三连 弹幕 护体 求链接 求资料 求源码 目录 空降 字幕 复习 学习 测试 第一天 同款".split())
TECH_NEUTRAL_CUE_WORDS = set("""
数据 页面 数据库 网站 业务 逻辑 代码 函数 变量 对象 方法 类 接口 课程 视频 插件 倍速
资料 笔记 格式 文件 链接 源码 字幕 目录 声音 播放 速度 基础 章节 java mysql sql html css
python csdn edge md 软件 工程师 学院 学生 老师 同学
""".split())
OBVIOUS_POSITIVE_CUE_WORDS = set("""
哈哈 哈哈哈 笑死 笑不活 乐死 好笑 搞笑 牛逼 太强 好棒 真棒 厉害 优秀 精彩 绝了
爱了 喜欢 舒服 爽 赞 yyds nb 666 好耶 学到了 学会了 干货 好兄弟
""".split())
OBVIOUS_POSITIVE_PATTERNS = [
    re.compile(r"哈{2,}"),
    re.compile(r"h{2,}", re.IGNORECASE),
    re.compile(r"233+"),
    re.compile(r"6{3,}"),
    re.compile(r"(真|太|很|超级)?牛(啊|哇|呀|逼|的|了|!|！|$)"),
]
OBVIOUS_NEGATIVE_CUE_WORDS = set("""
垃圾 恶心 烂 难受 下头 拉胯 看不下去 听不懂 无语 折磨 崩溃 烦 讨厌 尬 差 没用
入土 坐牢 裂开 破防 麻了 寄了 崩了 看不懂 学不会 不会 不行 太水
""".split())
AMBIGUOUS_POSITIVE_WORDS = set("好 强 牛".split())
AMBIGUOUS_NEGATIVE_WORDS = set("水".split())


def setup_chinese_font():
    font_candidates = [
        "C:/Windows/Fonts/msyh.ttc",      # Microsoft YaHei
        "C:/Windows/Fonts/simhei.ttf",    # SimHei
        "C:/Windows/Fonts/simsun.ttc",    # SimSun
        "/System/Library/Fonts/PingFang.ttc",
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
        "/usr/share/fonts/truetype/noto/NotoSansCJK-Regular.ttc",
    ]
    for font_path in font_candidates:
        path = Path(font_path)
        if path.exists():
            font_manager.fontManager.addfont(str(path))
            font_name = font_manager.FontProperties(fname=str(path)).get_name()
            plt.rcParams["font.sans-serif"] = [font_name]
            break
    plt.rcParams["axes.unicode_minus"] = False


def clean_text(text: str) -> str:
    text = str(text)
    text = re.sub(r"http\S+|www\.\S+", "", text)
    text = re.sub(r"\s+", "", text)
    text = re.sub(r"[^\u4e00-\u9fa5A-Za-z0-9!?！？。,.，]", "", text)
    return text


def read_word_file(path):
    words = set()
    if not path.exists():
        return words
    for encoding in ("utf-8-sig", "utf-8", "gbk"):
        try:
            lines = path.read_text(encoding=encoding).splitlines()
            break
        except UnicodeDecodeError:
            continue
    else:
        return words

    for line in lines:
        word = line.strip()
        if not word or word.startswith("#"):
            continue
        # 兼容 HowNet/知网词表中可能存在的空格、制表符、词性说明等格式。
        word = re.split(r"\s+", word)[0].strip()
        if word:
            words.add(word)
    return words


def load_sentiment_words():
    pos_files = [
        "hownet_positive.txt", "positive.txt", "pos.txt",
        "正面情感词语.txt", "正面评价词语.txt",
        "正面情感词语（中文）.txt", "正面评价词语（中文）.txt",
    ]
    neg_files = [
        "hownet_negative.txt", "negative.txt", "neg.txt",
        "负面情感词语.txt", "负面评价词语.txt",
        "负面情感词语（中文）.txt", "负面评价词语（中文）.txt",
    ]
    pos_words = set(DEFAULT_POS_WORDS)
    neg_words = set(DEFAULT_NEG_WORDS)
    for filename in pos_files:
        pos_words.update(read_word_file(LEXICON_DIR / filename))
    for filename in neg_files:
        neg_words.update(read_word_file(LEXICON_DIR / filename))
    # 弹幕短文本里单字词很容易误伤，例如“好了”不一定正面，“水”也可能不是负面。
    pos_words.difference_update(AMBIGUOUS_POSITIVE_WORDS)
    neg_words.difference_update(AMBIGUOUS_NEGATIVE_WORDS)
    return pos_words, neg_words


POS_WORDS, NEG_WORDS = load_sentiment_words()


def to_float(value, default=0.0):
    try:
        if pd.isna(value):
            return default
        return float(value)
    except (TypeError, ValueError):
        return default


def contains_positive_cue(text: str) -> bool:
    text = str(text).lower()
    if any(word.lower() in text for word in OBVIOUS_POSITIVE_CUE_WORDS):
        return True
    return any(pattern.search(text) for pattern in OBVIOUS_POSITIVE_PATTERNS)


def contains_negative_cue(text: str) -> bool:
    text = str(text)
    return any(word in text for word in OBVIOUS_NEGATIVE_CUE_WORDS)


def contains_neutral_cue(text: str) -> bool:
    text = str(text).lower()
    neutral_words = NEUTRAL_CUE_WORDS | TECH_NEUTRAL_CUE_WORDS
    return any(word.lower() in text for word in neutral_words)


def has_obvious_positive_cue(row) -> bool:
    text = str(row.get("text_clean", ""))
    if not contains_positive_cue(text):
        return False
    score = to_float(row.get("lexicon_score"))
    neg_count = to_float(row.get("neg_cnt"))
    negative_prob = to_float(row.get("prob_negative"))
    return score >= 0 and (neg_count == 0 or score >= LEXICON_STRONG_THRESHOLD) and negative_prob < 0.75


def has_obvious_negative_cue(row) -> bool:
    text = str(row.get("text_clean", ""))
    if not contains_negative_cue(text):
        return False
    score = to_float(row.get("lexicon_score"))
    pos_count = to_float(row.get("pos_cnt"))
    positive_prob = to_float(row.get("prob_positive"))
    return score <= 0 and (pos_count == 0 or score <= -LEXICON_STRONG_THRESHOLD) and positive_prob < 0.75


def should_keep_neutral(row) -> bool:
    text = str(row.get("text_clean", ""))
    positive_prob = to_float(row.get("prob_positive"))
    negative_prob = to_float(row.get("prob_negative"))
    neutral_prob = to_float(row.get("prob_neutral"))
    best_polar_prob = max(positive_prob, negative_prob)
    lexicon_abs = to_float(row.get("lexicon_abs_score"))
    raw_label = row.get("pred_raw_label", "")

    if has_obvious_positive_cue(row) or has_obvious_negative_cue(row):
        return False

    if lexicon_abs == 0:
        if raw_label == "中性" and neutral_prob >= 0.42:
            return True
        if neutral_prob >= 0.50 and neutral_prob >= best_polar_prob - 0.02:
            return True
        if contains_neutral_cue(text) and neutral_prob >= 0.35 and best_polar_prob < 0.55:
            return True
        if neutral_prob >= 0.35 and abs(positive_prob - negative_prob) < 0.15 and best_polar_prob < 0.45:
            return True

    # 只有一个弱情感词，且模型明显偏中性时，不让词典把它硬拽到正/负面。
    if lexicon_abs <= 1 and raw_label == "中性" and neutral_prob >= 0.55 and best_polar_prob < 0.35:
        return True

    return False


def is_obvious_auto_label(row) -> bool:
    if row.get("pred_label") == "正面" and has_obvious_positive_cue(row):
        return True
    if row.get("pred_label") == "负面" and has_obvious_negative_cue(row):
        return True
    if (
        row.get("pred_label") == "中性"
        and to_float(row.get("prob_neutral")) >= 0.85
        and to_float(row.get("lexicon_abs_score")) == 0
        and to_float(row.get("model_confidence")) >= 0.8
    ):
        return True
    return False


def normalize_label(value, legacy_feedback_label=False):
    if pd.isna(value):
        return np.nan
    text = str(value).strip().lower()
    if not text:
        return np.nan
    if legacy_feedback_label:
        if text == "0":
            return -1
        if text == "2":
            return 0
    if text in LABEL_VALUES:
        return LABEL_VALUES[text]
    try:
        number = int(float(text))
    except ValueError:
        return np.nan
    return number if number in LABEL_NAMES else np.nan


def sentiment_features(text: str):
    words = [w for w in tokenize(text) if w not in STOP_WORDS]
    pos = 0
    neg = 0
    score = 0.0
    pos_score = 0.0
    neg_score = 0.0
    matched_spans = set()

    for i, word in enumerate(words):
        polarity = 1 if word in POS_WORDS else -1 if word in NEG_WORDS else 0
        if polarity == 0:
            continue
        window = words[max(0, i - 2):i]
        weight = 1.0
        for prev in window:
            weight *= DEGREE_WORDS.get(prev, 1.0)
        if any(prev in NEGATION_WORDS for prev in window):
            polarity *= -1
        if polarity > 0:
            pos += 1
            pos_score += abs(weight)
        else:
            neg += 1
            neg_score += abs(weight)
        score += polarity * weight

    # 处理 jieba 没切出来的多字情感词，例如“听不懂”“看不下去”“太强”。
    for lexicon, polarity in ((POS_WORDS, 1), (NEG_WORDS, -1)):
        for term in lexicon:
            if len(term) <= 1 or term not in text:
                continue
            key = (term, polarity)
            if key in matched_spans:
                continue
            matched_spans.add(key)
            if polarity > 0:
                pos += 1
                pos_score += 1.0
            else:
                neg += 1
                neg_score += 1.0
            score += polarity

    length = len(words)
    exclaim = text.count("!") + text.count("！")
    question = text.count("?") + text.count("？")
    density = (pos + neg) / max(length, 1)
    return pos, neg, length, exclaim, question, score, pos_score, neg_score, abs(score), density


def prepare_dataframe(df, legacy_binary_label=False):
    if "label" not in df.columns:
        df["label"] = np.nan
    if legacy_binary_label:
        raw_label = df["label"].copy()
        normalized = raw_label.map(normalize_label)
        legacy_negative = raw_label.astype(str).str.strip().eq("0")
        normalized.loc[legacy_negative] = -1
        df["label"] = normalized
    else:
        df["label"] = df["label"].map(normalize_label)
    df["text_clean"] = df["text"].map(clean_text)
    df = df[df["text_clean"].str.len() > 0].drop_duplicates(["partition", "bvid", "text_clean"]).copy()
    feats = df["text_clean"].map(sentiment_features)
    df[SENTIMENT_COLUMNS] = pd.DataFrame(feats.tolist(), index=df.index)
    return df


def load_and_prepare(path):
    df = pd.read_csv(path, encoding="utf-8-sig")
    return prepare_dataframe(df, legacy_binary_label=Path(path).name == TRAIN_DATA_PATH.name)


def make_neutral_seed_df():
    rows = [
        {"partition": "中性种子", "bvid": "neutral_seed", "text": text, "label": 0}
        for text in NEUTRAL_SEED_TEXTS
    ]
    return pd.DataFrame(rows)


def load_feedback_data(feedback_dir=FEEDBACK_DIR):
    paths = []
    feedback_dir = Path(feedback_dir)
    if feedback_dir.exists():
        paths.extend(feedback_dir.glob("*.csv"))
    if RESULT_DIR.exists():
        paths.extend(RESULT_DIR.glob("**/review_samples.csv"))
        paths.extend(RESULT_DIR.glob("**/manual_labels.csv"))
    paths = sorted(set(paths), key=lambda p: p.stat().st_mtime)

    rows = []
    for path in paths:
        try:
            df = pd.read_csv(path, encoding="utf-8-sig")
        except Exception:
            continue
        label_col = "review_label" if "review_label" in df.columns else "label" if "label" in df.columns else None
        if not label_col or "text" not in df.columns:
            continue
        for _, row in df.iterrows():
            legacy_feedback_label = (
                path.name == "review_samples.csv"
                and "label_schema" not in df.columns
                and label_col == "review_label"
            )
            label = normalize_label(row.get(label_col), legacy_feedback_label=legacy_feedback_label)
            if pd.isna(label):
                continue
            rows.append({
                "partition": row.get("partition", "人工反馈"),
                "bvid": row.get("bvid", path.stem),
                "text": row["text"],
                "label": int(label),
            })

    if not rows:
        return pd.DataFrame(columns=["partition", "bvid", "text", "label"])
    feedback = pd.DataFrame(rows)
    feedback["text_clean_key"] = feedback["text"].map(clean_text)
    feedback = feedback[feedback["text_clean_key"].str.len() > 0].copy()
    feedback = feedback.drop_duplicates(["text_clean_key"], keep="last")
    return feedback.drop(columns=["text_clean_key"])


def get_reviewed_texts(feedback_dir=FEEDBACK_DIR):
    feedback = load_feedback_data(feedback_dir)
    if feedback.empty:
        return set()
    return {clean_text(text) for text in feedback["text"].astype(str) if clean_text(text)}


def plot_bar(df, path):
    plt.figure(figsize=(7, 4.2))
    pivot = df.pivot(index="partition", columns="pred_label", values="ratio").fillna(0)
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


def plot_metrics(metrics, path):
    plt.figure(figsize=(7, 4.2))
    x = np.arange(len(metrics))
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


def plot_confusion_matrix(cm, path):
    plt.figure(figsize=(5.2, 4.6))
    plt.imshow(cm, cmap="Blues")
    plt.title("最优模型混淆矩阵")
    plt.colorbar(fraction=0.046, pad=0.04)
    ticks = np.arange(len(ORDERED_LABEL_NAMES))
    plt.xticks(ticks, ORDERED_LABEL_NAMES)
    plt.yticks(ticks, ORDERED_LABEL_NAMES)
    plt.xlabel("预测标签")
    plt.ylabel("真实标签")
    threshold = cm.max() / 2 if cm.size and cm.max() else 0
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            color = "white" if cm[i, j] > threshold else "black"
            plt.text(j, i, str(cm[i, j]), ha="center", va="center", color=color)
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


def plot_keywords(df, path):
    texts = "".join(df["text_clean"].astype(str).tolist())
    words = tokenize(texts)
    freq = {}
    for w in words:
        if w in STOP_WORDS or len(w.strip()) == 0:
            continue
        freq[w] = freq.get(w, 0) + 1
    top = sorted(freq.items(), key=lambda x: x[1], reverse=True)[:15]
    labels = [i[0] for i in top][::-1]
    values = [i[1] for i in top][::-1]
    plt.figure(figsize=(7, 4.2))
    plt.barh(labels, values)
    plt.xlabel("词频")
    plt.title("弹幕高频词 Top15")
    plt.tight_layout()
    plt.savefig(path, dpi=200)
    plt.close()


def predict_with_confidence(model, X):
    if hasattr(model, "predict_proba"):
        proba = model.predict_proba(X)
        index = np.argmax(proba, axis=1)
        pred = model.classes_[index]
        confidence = proba[np.arange(len(index)), index]
        return pred, confidence, proba, model.classes_

    if hasattr(model, "decision_function"):
        score = model.decision_function(X)
        if score.ndim == 1:
            prob_pos = 1 / (1 + np.exp(-score))
            proba = np.vstack([1 - prob_pos, prob_pos]).T
            classes = model.classes_
            index = np.argmax(proba, axis=1)
            pred = classes[index]
            confidence = np.maximum(prob_pos, 1 - prob_pos)
            return pred, confidence, proba, classes

        exp_score = np.exp(score - score.max(axis=1, keepdims=True))
        proba = exp_score / exp_score.sum(axis=1, keepdims=True)
        index = np.argmax(proba, axis=1)
        pred = model.classes_[index]
        confidence = proba[np.arange(len(index)), index]
        return pred, confidence, proba, model.classes_

    pred = model.predict(X)
    confidence = np.ones(len(pred))
    proba = np.ones((len(pred), 1))
    return pred, confidence, proba, np.array([pred[0]]) if len(pred) else np.array([])


def add_class_probabilities(df, proba, classes):
    class_to_column = {-1: "prob_negative", 0: "prob_neutral", 1: "prob_positive"}
    for column in class_to_column.values():
        df[column] = 0.0
    for idx, cls in enumerate(classes):
        column = class_to_column.get(int(cls))
        if column:
            df[column] = proba[:, idx]
    return df


def assign_display_label(row):
    score = row["lexicon_score"]
    positive_prob = row.get("prob_positive", 0.0)
    negative_prob = row.get("prob_negative", 0.0)
    neutral_prob = row.get("prob_neutral", 0.0)
    best_polar_prob = max(positive_prob, negative_prob)
    lexicon_abs = row.get("lexicon_abs_score", 0.0)
    raw_label = row.get("pred_raw_label", "")
    has_neutral_cue = contains_neutral_cue(row.get("text_clean", ""))

    if has_obvious_positive_cue(row):
        return "正面"
    if has_obvious_negative_cue(row):
        return "负面"

    if positive_prob >= MODEL_STRONG_THRESHOLD and negative_prob < 0.2:
        return "正面"
    if negative_prob >= MODEL_STRONG_THRESHOLD and positive_prob < 0.2:
        return "负面"

    if should_keep_neutral(row):
        return "中性"

    if score >= 2 or (score >= LEXICON_STRONG_THRESHOLD and positive_prob >= 0.45 and positive_prob >= neutral_prob):
        return "正面"
    if score <= -2 or (score <= -LEXICON_STRONG_THRESHOLD and negative_prob >= 0.45 and negative_prob >= neutral_prob):
        return "负面"

    if neutral_prob >= NEUTRAL_STRICT_THRESHOLD and best_polar_prob < 0.35:
        return "中性"
    if (
        neutral_prob >= 0.55
        and best_polar_prob < 0.45
        and has_neutral_cue
        and lexicon_abs <= 1
    ):
        return "中性"

    if raw_label == "中性" and lexicon_abs == 0 and neutral_prob >= 0.35:
        return "中性"
    if lexicon_abs == 0 and neutral_prob >= 0.30 and abs(positive_prob - negative_prob) < 0.08:
        return "中性"

    if lexicon_abs > 0:
        return "正面" if score > 0 else "负面"
    if positive_prob >= negative_prob:
        return "正面"
    return "负面"


def review_reason(row):
    score = row["lexicon_score"]
    raw = row["pred_raw_label"]
    confidence = row["model_confidence"]
    if confidence < MODEL_CONFIDENCE_THRESHOLD:
        return "模型低置信度"
    if score >= LEXICON_STRONG_THRESHOLD and raw == "负面":
        return "词典偏正但模型偏负"
    if score <= -LEXICON_STRONG_THRESHOLD and raw == "正面":
        return "词典偏负但模型偏正"
    if row["pred_label"] == "中性" and row["lexicon_abs_score"] > 0:
        return "中性结果含情感词"
    return "代表样本"


def create_review_samples(df, path, review_ratio=REVIEW_SAMPLE_RATIO, reviewed_texts=None):
    columns = [
        "review_label", "label_schema", "review_reason", "partition", "bvid", "text",
        "pred_label", "pred_raw_label", "model_confidence", "lexicon_score",
        "prob_positive", "prob_neutral", "prob_negative",
        "pos_cnt", "neg_cnt", "word_len",
    ]
    review_df = df.copy()
    reviewed_clean_texts = {clean_text(text) for text in (reviewed_texts or set()) if clean_text(text)}
    if reviewed_clean_texts:
        review_df = review_df[~review_df["text_clean"].astype(str).isin(reviewed_clean_texts)].copy()
    review_df = review_df.drop_duplicates(["text_clean"]).copy()
    if not review_df.empty:
        obvious_mask = review_df.apply(is_obvious_auto_label, axis=1)
        review_df = review_df[~obvious_mask].copy()
    if review_df.empty:
        empty = pd.DataFrame(columns=columns)
        empty.to_csv(path, index=False, encoding="utf-8-sig")
        return path, 0, review_ratio

    target_count = min(MAX_REVIEW_SAMPLE_COUNT, max(1, int(np.ceil(len(review_df) * review_ratio))))
    review_df["review_reason"] = review_df.apply(review_reason, axis=1)
    review_df["sort_score"] = (
        (1 - review_df["model_confidence"].clip(0, 1)) * 3
        + review_df["lexicon_abs_score"].clip(0, 3)
        + (review_df["review_reason"] != "代表样本").astype(int)
    )

    parts = []
    priority = review_df[review_df["review_reason"] != "代表样本"].sort_values("sort_score", ascending=False)
    if not priority.empty:
        parts.append(priority.head(target_count))
    for label in ["正面", "负面", "中性"]:
        subset = review_df[
            (review_df["pred_label"] == label)
            & (review_df["model_confidence"] < MODEL_CONFIDENCE_THRESHOLD)
        ].sort_values("sort_score", ascending=False)
        if not subset.empty:
            parts.append(subset.head(max(1, int(target_count * 0.1))))
    if parts:
        sampled = pd.concat(parts).drop_duplicates(["partition", "bvid", "text_clean"])
    else:
        sampled = review_df[review_df["model_confidence"] < MODEL_CONFIDENCE_THRESHOLD].sort_values("sort_score", ascending=False)
    sampled = sampled.head(target_count)

    sampled = sampled.copy()
    sampled.insert(0, "review_label", "")
    sampled.insert(1, "label_schema", "1=正面,0=中性,-1=负面")
    sampled[columns].to_csv(path, index=False, encoding="utf-8-sig")
    return path, len(sampled), review_ratio


def export_label_groups(df, result_dir):
    export_columns = [
        "partition", "bvid", "text", "pred_label", "pred_raw_label",
        "model_confidence", "prob_positive", "prob_neutral", "prob_negative",
        "lexicon_score", "pos_cnt", "neg_cnt", "manual_override", "manual_label",
    ]
    export_columns = [column for column in export_columns if column in df.columns]
    label_files = {
        "正面": "positive_comments.csv",
        "负面": "negative_comments.csv",
        "中性": "neutral_comments.csv",
    }
    paths = {}
    for label, filename in label_files.items():
        subset = df[df["pred_label"] == label].copy()
        subset[export_columns].to_csv(result_dir / filename, index=False, encoding="utf-8-sig")
        paths[label] = result_dir / filename
    return paths


def export_diagnostics(df, result_dir):
    confidence_summary = (
        df.groupby(["partition", "pred_label"])
        .agg(
            count=("text", "size"),
            mean_confidence=("model_confidence", "mean"),
            mean_positive_prob=("prob_positive", "mean"),
            mean_neutral_prob=("prob_neutral", "mean"),
            mean_negative_prob=("prob_negative", "mean"),
            mean_lexicon_score=("lexicon_score", "mean"),
        )
        .reset_index()
    )
    confidence_summary.to_csv(result_dir / "confidence_summary.csv", index=False, encoding="utf-8-sig")

    video_stat = df.groupby(["partition", "bvid", "pred_label"]).size().reset_index(name="count")
    video_total = df.groupby(["partition", "bvid"]).size().reset_index(name="total")
    video_stat = video_stat.merge(video_total, on=["partition", "bvid"])
    video_stat["ratio"] = video_stat["count"] / video_stat["total"]
    if "title" in df.columns:
        title_map = df.groupby(["partition", "bvid"])["title"].first().reset_index()
        video_stat = video_stat.merge(title_map, on=["partition", "bvid"], how="left")
        cols = ["partition", "bvid", "title", "pred_label", "count", "total", "ratio"]
        video_stat = video_stat[cols]
    video_stat.to_csv(result_dir / "video_sentiment_stats.csv", index=False, encoding="utf-8-sig")

    low_n = max(1, int(np.ceil(len(df) * REVIEW_SAMPLE_RATIO)))
    low_conf = df.sort_values("model_confidence", ascending=True).head(low_n)
    low_conf.to_csv(result_dir / "low_confidence_samples.csv", index=False, encoding="utf-8-sig")

    conflict = df[
        ((df["lexicon_score"] >= LEXICON_STRONG_THRESHOLD) & (df["pred_raw_label"] == "负面"))
        | ((df["lexicon_score"] <= -LEXICON_STRONG_THRESHOLD) & (df["pred_raw_label"] == "正面"))
        | ((df["pred_label"] == "中性") & (df["lexicon_abs_score"] > 0))
    ].copy()
    conflict.to_csv(result_dir / "conflict_samples.csv", index=False, encoding="utf-8-sig")

    return {
        "confidence_summary": result_dir / "confidence_summary.csv",
        "video_sentiment_stats": result_dir / "video_sentiment_stats.csv",
        "low_confidence_samples": result_dir / "low_confidence_samples.csv",
        "conflict_samples": result_dir / "conflict_samples.csv",
        "low_confidence_count": len(low_conf),
        "conflict_count": len(conflict),
    }


def save_iteration_comparison(current_stat, result_dir):
    candidates = []
    if RESULT_DIR.exists():
        for path in RESULT_DIR.glob("**/partition_sentiment_stats.csv"):
            if path.parent.resolve() == result_dir.resolve():
                continue
            candidates.append(path)
    if not candidates:
        return None
    previous_path = max(candidates, key=lambda p: p.stat().st_mtime)
    previous = pd.read_csv(previous_path, encoding="utf-8-sig")
    merged = current_stat.merge(
        previous[["partition", "pred_label", "ratio"]].rename(columns={"ratio": "previous_ratio"}),
        on=["partition", "pred_label"],
        how="outer",
    )
    merged["ratio"] = merged["ratio"].fillna(0)
    merged["previous_ratio"] = merged["previous_ratio"].fillna(0)
    merged["delta_ratio"] = merged["ratio"] - merged["previous_ratio"]
    merged["previous_experiment"] = previous_path.parent.name
    out = result_dir / "iteration_comparison.csv"
    merged.to_csv(out, index=False, encoding="utf-8-sig")
    return out


def write_analysis_summary(path, summary_data):
    stat = summary_data["stat"].copy()
    metrics = summary_data["metrics"].copy()
    best_row = metrics.iloc[0]
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
    return path


def analyze(
    train_data_path=TRAIN_DATA_PATH,
    predict_data_path=None,
    result_dir=RESULT_DIR,
    fig_dir=FIG_DIR,
    feedback_dir=FEEDBACK_DIR,
):
    train_data_path = Path(train_data_path)
    result_dir = Path(result_dir)
    fig_dir = Path(fig_dir)
    result_dir.mkdir(parents=True, exist_ok=True)
    fig_dir.mkdir(parents=True, exist_ok=True)

    setup_chinese_font()

    train_df = load_and_prepare(train_data_path)
    neutral_seed_df = prepare_dataframe(make_neutral_seed_df())
    feedback_raw = load_feedback_data(feedback_dir)
    feedback_df = prepare_dataframe(feedback_raw) if not feedback_raw.empty else feedback_raw
    train_parts = [train_df, neutral_seed_df]
    if not feedback_df.empty:
        train_parts.append(feedback_df)
    train_df = pd.concat(train_parts, ignore_index=True).drop_duplicates(["text_clean"], keep="last")
    feedback_label_map = {}
    if not feedback_df.empty:
        feedback_label_map = (
            feedback_df[feedback_df["label"].notna()]
            .drop_duplicates(["text_clean"], keep="last")
            .set_index("text_clean")["label"]
            .astype(int)
            .to_dict()
        )

    predict_path = Path(predict_data_path) if predict_data_path else RAW_DATA_PATH if RAW_DATA_PATH.exists() else train_data_path
    predict_df = load_and_prepare(predict_path)

    labeled = train_df[train_df["label"].notna()].copy()
    y = labeled["label"].astype(int)
    word_vectorizer = TfidfVectorizer(
        tokenizer=tokenize,
        token_pattern=None,
        max_features=WORD_TFIDF_MAX_FEATURES,
        ngram_range=(1, 2),
        sublinear_tf=True,
    )
    char_vectorizer = TfidfVectorizer(
        analyzer="char",
        max_features=CHAR_TFIDF_MAX_FEATURES,
        ngram_range=(2, 4),
        sublinear_tf=True,
    )
    X_word = word_vectorizer.fit_transform(labeled["text_clean"])
    X_char = char_vectorizer.fit_transform(labeled["text_clean"])
    X_extra = csr_matrix(labeled[FEATURE_COLUMNS].values)
    X = hstack([X_word, X_char, X_extra])

    class_counts = y.value_counts()
    stratify = y if len(class_counts) > 1 and class_counts.min() >= 2 else None
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=stratify)
    models = {
        "朴素贝叶斯": MultinomialNB(),
        "逻辑回归": LogisticRegression(max_iter=1000, class_weight="balanced"),
        "SVM": LinearSVC(max_iter=5000, class_weight="balanced"),
        "随机森林": RandomForestClassifier(n_estimators=160, random_state=42, class_weight="balanced_subsample"),
    }

    rows = []
    trained = {}
    test_predictions = {}
    for name, model in models.items():
        model.fit(X_train, y_train)
        pred = model.predict(X_test)
        rows.append({
            "model": name,
            "accuracy": accuracy_score(y_test, pred),
            "f1": f1_score(y_test, pred, average="macro", zero_division=0),
        })
        trained[name] = model
        test_predictions[name] = pred
    metrics = pd.DataFrame(rows).sort_values("f1", ascending=False)
    metrics.to_csv(result_dir / "model_metrics.csv", index=False, encoding="utf-8-sig")
    plot_metrics(metrics, fig_dir / "model_metrics.png")

    best_name = metrics.iloc[0]["model"]
    best_model = trained[best_name]
    best_test_pred = test_predictions[best_name]
    report = classification_report(
        y_test,
        best_test_pred,
        labels=ORDERED_LABELS,
        target_names=ORDERED_LABEL_NAMES,
        output_dict=True,
        zero_division=0,
    )
    pd.DataFrame(report).transpose().to_csv(result_dir / "classification_report_full.csv", encoding="utf-8-sig")
    cm = confusion_matrix(y_test, best_test_pred, labels=ORDERED_LABELS)
    pd.DataFrame(cm, index=ORDERED_LABEL_NAMES, columns=ORDERED_LABEL_NAMES).to_csv(
        result_dir / "confusion_matrix.csv",
        encoding="utf-8-sig",
    )
    plot_confusion_matrix(cm, fig_dir / "confusion_matrix.png")

    X_all = hstack([
        word_vectorizer.transform(predict_df["text_clean"]),
        char_vectorizer.transform(predict_df["text_clean"]),
        csr_matrix(predict_df[FEATURE_COLUMNS].values)
    ])
    pred, confidence, proba, classes = predict_with_confidence(best_model, X_all)
    predict_df["pred"] = pred
    predict_df["model_confidence"] = confidence
    predict_df = add_class_probabilities(predict_df, proba, classes)
    predict_df["pred_raw_label"] = predict_df["pred"].map(LABEL_NAMES)
    predict_df["pred_label"] = predict_df.apply(assign_display_label, axis=1)
    predict_df["manual_label"] = predict_df["text_clean"].map(feedback_label_map)
    predict_df["manual_override"] = predict_df["manual_label"].notna()
    if predict_df["manual_override"].any():
        manual_labels = predict_df.loc[predict_df["manual_override"], "manual_label"].astype(int)
        predict_df.loc[predict_df["manual_override"], "pred_label"] = manual_labels.map(LABEL_NAMES)
    predict_df.to_csv(result_dir / "danmu_predicted.csv", index=False, encoding="utf-8-sig")
    label_group_paths = export_label_groups(predict_df, result_dir)
    diagnostics = export_diagnostics(predict_df, result_dir)

    stat = predict_df.groupby(["partition", "pred_label"]).size().reset_index(name="count")
    total = predict_df.groupby("partition").size().reset_index(name="total")
    stat = stat.merge(total, on="partition")
    stat["ratio"] = stat["count"] / stat["total"]
    stat.to_csv(result_dir / "partition_sentiment_stats.csv", index=False, encoding="utf-8-sig")
    iteration_comparison_path = save_iteration_comparison(stat, result_dir)
    plot_bar(stat, fig_dir / "partition_sentiment.png")
    plot_keywords(predict_df, fig_dir / "keywords_top15.png")
    reviewed_texts = set(feedback_df["text_clean"].astype(str)) if not feedback_df.empty else set()
    review_path, review_count, review_ratio = create_review_samples(
        predict_df,
        result_dir / "review_samples.csv",
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
    return summary


def main():
    summary = analyze()
    print(f"完成。训练数据：{summary['train_data_path'].name}，预测数据：{summary['predict_path'].name}")
    print("结果保存在 results/ 和 figures/。")
    metrics = summary["metrics"]
    stat = summary["stat"]
    print(metrics)
    print(stat)


if __name__ == "__main__":
    main()
