# B站学习区与生活区弹幕情感对比分析

## 项目简介

本项目输入一个学习区视频和一个生活区视频，自动完成弹幕采集、中文文本清洗、四模型训练、三分类情感预测、人工主动学习和结果归档。

情感标签统一为：

- `1`：正面
- `0`：中性
- `-1`：负面

## 快速使用

在项目根目录打开 PowerShell，首次运行安装依赖：

```powershell
python -m pip install -r requirements.txt
```

随后用 VS Code 或 Jupyter 打开：

```text
src/run_experiment.ipynb
```

点击 `Run All / 全部运行`，依次输入：

1. 本次实验名称，直接回车会使用时间戳。
2. 学习区视频 BV 号或完整链接。
3. 生活区视频 BV 号或完整链接。

程序会连续运行四轮：

```text
爬取弹幕
-> 第1轮分析 -> 人工标注最多100条
-> 第2轮分析 -> 人工标注最多100条
-> 第3轮分析 -> 人工标注最多100条
-> 第4轮最终分析
```

人工复核输入规则：

```text
1  = 正面
0  = 中性
-1 = 负面
回车 = 跳过
q  = 提前结束本轮复核
```

最终结果位于：

```text
results/实验名称/final_round_4/
figures/实验名称/final_round_4/
```

## 当前分析方法

项目不再只依赖简单正负词计数，而是组合以下信息：

- `jieba` 词级 TF-IDF。
- 中文字级 2-4gram TF-IDF，用于网络短语、错别字和弹幕梗。
- HowNet/知网正负面情感词典。
- 最长情感短语优先匹配，避免“看不懂”再次匹配“懂”。
- 否定词、程度副词和弹幕式表达。
- “但是、不过、虽然”等篇章转折与让步关系。
- 情感对象、方面、认知状态、自身情绪、立场和混合情感。
- 历史人工标注，人工标签优先级最高。
- 朴素贝叶斯、逻辑回归、SVM、随机森林四模型比较。

模型评估后，程序会使用全部已标注样本重新训练最优模型，再预测真实弹幕。

## 重要输出

最终轮建议优先查看：

- `danmu_predicted.csv`：每条弹幕的模型概率、词典分数、细粒度属性和最终标签。
- `positive_comments.csv`：最终正面弹幕。
- `neutral_comments.csv`：最终中性弹幕。
- `negative_comments.csv`：最终负面弹幕。
- `partition_sentiment_stats.csv`：学习区与生活区的三类情感占比。
- `classification_report_full.csv`：精确率、召回率和 F1。
- `confusion_matrix.csv`：混淆矩阵原始数据。
- `confidence_summary.csv`：各类别平均置信度。
- `low_confidence_samples.csv`：低置信样本。
- `conflict_samples.csv`：模型与词典冲突样本。
- `review_samples.csv`：下一轮建议人工复核的样本。
- `sentiment_type_stats.csv`：对象评价、自身情绪、认知状态、立场等类型统计。
- `aspect_sentiment_stats.csv`：不同方面的情感统计。
- `mixed_sentiment_samples.csv`：同时包含正负表达的混合情感样本。
- `analysis_summary.md`：自动实验摘要。

图表位于对应的 `figures/实验名称/final_round_4/`。

## 数据与历史标签

- `data/danmu_sample_5000.csv`：初始训练样本。
- `data/feedback/manual_labels_history.csv`：历次人工复核合并后的长期训练资产。
- `data/sentiment_lexicon/`：HowNet/知网情感词典。
- `data/experiments/实验名称/raw_bilibili_danmu.csv`：每次实验采集的原始弹幕。

程序会自动读取 `data/feedback/*.csv` 和现有结果中的已填写复核标签。已经人工标注过的文本不会重复询问。

## 代码文件

- `src/run_experiment.ipynb`：一键四轮实验入口。
- `src/crawler_bilibili.ipynb`：B站视频信息和弹幕采集。
- `src/train_analyze.ipynb`：清洗、特征、模型、预测、统计和可视化核心。
- `src/make_sample_data.ipynb`：缺少训练样本时生成演示数据。
- `annotated_code/`：对应代码的注释阅读版，不参与正式运行。

更完整的文件说明见 `项目文件讲解.md`。

## 当前验证表现

使用保留测试集验证时，当前最优模型为随机森林：

- 准确率：约 `79.82%`
- 宏平均 F1：约 `72.92%`
- 负面召回率：约 `55%`

这些数值是模型验证指标，不等于每条真实弹幕都一定正确。继续完成三轮人工复核，通常能进一步改善与你所选视频相关的表达判断。
