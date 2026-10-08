# 情感词典说明

项目使用两层词典：

1. `src/train_analyze.ipynb` 内的默认小词表，用于提供稳定兜底词。
2. `data/sentiment_lexicon/` 中的 HowNet/知网正负面词典，作为主要外部词典。

当前文件：

- `data/sentiment_lexicon/hownet_positive.txt`
- `data/sentiment_lexicon/hownet_negative.txt`

程序会清洗、去重并合并词典。情感匹配采用“最长短语优先且不重叠”的方式，避免短词重复计分。

词典主要用于：

- 生成正负情感词数量与分数。
- 辅助模型训练。
- 分析转折、混合情感和情感方面。
- 发现模型与词典冲突的待复核样本。

词典不是最终裁判。网络梗、反讽、上下文和新词仍需要机器学习概率及人工复核共同处理。
