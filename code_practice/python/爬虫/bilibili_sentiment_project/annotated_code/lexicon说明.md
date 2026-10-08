# 情感词典说明

`train_analyze_annotated.py` 里看到的 `DEFAULT_POS_WORDS` 和 `DEFAULT_NEG_WORDS` 不是完整词典，只是兜底小词表。

真正参与分析的是：

- `data/sentiment_lexicon/hownet_positive.txt`：正面词典，约 1226 行。
- `data/sentiment_lexicon/hownet_negative.txt`：负面词典，约 1413 行。

程序在 `load_sentiment_words()` 里会这样做：

1. 先读取 `DEFAULT_POS_WORDS`、`DEFAULT_NEG_WORDS`。
2. 再读取 `data/sentiment_lexicon/` 下面的 HowNet/知网词典文件。
3. 最后合并成 `POS_WORDS` 和 `NEG_WORDS`。

所以模型实际使用的是合并后的大词典，不是截图里那几十个默认词。
