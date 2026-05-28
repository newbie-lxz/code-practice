# B站学习区与生活区弹幕情感对比分析

## 快速使用

在项目根目录打开 PowerShell，也就是：

```powershell
文件路径：bilibili_sentiment_project
```

第一次运行先安装依赖：

```powershell
python -m pip install -r requirements.txt
```

然后运行一键实验脚本：

```powershell
python src\run_experiment.py
```

程序会依次让你输入：

```text
实验名称（可直接回车，以时间戳命名，即实验时间like: experiment_20260528_142605）
学习区视频 BV 号或视频链接
生活区视频 BV 号或视频链接
```

![image-20260528151132385](C:\Users\15277\AppData\Roaming\Typora\typora-user-images\image-20260528151132385.png)

运行流程是：

```text
爬取弹幕 -> 第1轮分析 -> 人工标注最多100条 -> 第2轮分析 -> 人工标注最多100条
-> 第3轮分析 -> 人工标注最多100条 -> 第4轮最终分析
```

人工标注时直接在终端输入：

```text
1  = 正面
0  = 中性
-1 = 负面
回车 = 跳过
q  = 结束本轮人工复核
```

最终结果看这里：

```text
results/实验名称/final_round_4/
figures/实验名称/final_round_4/
```

最常看的文件：

- `results/实验名称/final_round_4/danmu_predicted.csv`：每条弹幕的最终分类结果。
- `results/实验名称/final_round_4/positive_comments.csv`：正面弹幕。
- `results/实验名称/final_round_4/negative_comments.csv`：负面弹幕。
- `results/实验名称/final_round_4/neutral_comments.csv`：中性弹幕。
- `results/实验名称/final_round_4/partition_sentiment_stats.csv`：学习区/生活区情感占比。
- `results/实验名称/final_round_4/analysis_summary.md`：自动生成的实验摘要。
- `figures/实验名称/final_round_4/partition_sentiment.png`：学习区/生活区情感对比图。
- `figures/实验名称/final_round_4/keywords_top15.png`：高频词图。
- `figures/实验名称/final_round_4/confusion_matrix.png`：模型混淆矩阵。

## 交付内容

- `B站弹幕情感对比分析_6分钟展示PPT.pptx`：课堂展示用PPT，控制在6分钟内。
- `基于大数据爬虫与机器学习的B站弹幕情感对比分析_项目报告.docx`：完整项目报告。
- `src/crawler_bilibili.py`：B站弹幕采集脚本模板，填入真实BV号后可采集弹幕。
- `src/train_analyze.py`：清洗、特征工程、模型训练、预测、可视化主程序。
- `src/run_experiment.py`：一键实验脚本，运行后输入学习区和生活区BV号，自动完成爬取、分析和归档。
- `src/make_sample_data.py`：课堂演示用样例数据生成脚本。
- `annotated_code/`：所有源码的逐行注释阅读版，独立文件夹，读完可直接删除。
- `data/sentiment_lexicon/`：情感词典目录，支持放入 HowNet/知网正负情感词典文本文件。
- `data/danmu_sample_5000.csv`：5000条可复现实验样例数据，其中1000条带人工标注字段。
- `results/`：模型指标、预测结果、分区情感统计结果。
- `figures/`：模型对比图、分区情感图、高频词图。

## 重要说明

当前压缩包内的数据是“课堂演示用样例数据”，用于保证项目可直接运行和展示。正式提交如果要求真实爬取B站数据，请先运行或修改 `src/crawler_bilibili.py`，把采集到的数据整理成如下字段：

```text
partition,bvid,text,label
```

其中 `label` 只需要给人工标注的1000条填写，未标注样本可留空。

## 运行方式

推荐使用四轮主动学习实验脚本：

```bash
pip install -r requirements.txt
python src/run_experiment.py
```

程序会提示输入：

```text
实验名称
学习区BV号或视频链接
生活区BV号或视频链接
```

运行后会按实验名称自动归档：

- `data/experiments/实验名称/raw_bilibili_danmu.csv`：本次爬取的原始弹幕。
- `results/实验名称/round_1`、`round_2`、`round_3`：前三轮主动学习分析结果。
- `results/实验名称/final_round_4`：最终结果。
- `figures/实验名称/round_1`、`round_2`、`round_3`：前三轮图表。
- `figures/实验名称/final_round_4`：最终图表。

`results/实验名称/` 中还会额外导出：

- `positive_comments.csv`：模型判为正面的弹幕。
- `negative_comments.csv`：模型判为负面的弹幕。
- `neutral_comments.csv`：模型判为中性的弹幕。
- `analysis_summary.md`：本轮实验自动摘要。
- `classification_report_full.csv`：最优模型完整分类报告。
- `confusion_matrix.csv`：最优模型混淆矩阵。
- `confidence_summary.csv`：按分区和情感类别统计置信度。
- `low_confidence_samples.csv`：模型低置信样本。
- `conflict_samples.csv`：词典与模型冲突样本。
- `video_sentiment_stats.csv`：按视频统计情感分布。
- `iteration_comparison.csv`：与上一轮实验的比例变化对比。

采集量说明：

- 作业目标为总计约5000条弹幕，学习区、生活区各约2500条。
- 一键脚本会对每个BV最多保留2500条弹幕；如果视频本身可获取弹幕不足，会按实际数量继续完成分析，并在实验摘要中记录差额。
- 爬虫输出包含 `partition,bvid,title,view_count,like_count,coin_count,favorite_count,reply_count,danmaku_count,text` 等字段。

情感词典说明：

- 默认读取 `data/sentiment_lexicon/hownet_positive.txt` 和 `data/sentiment_lexicon/hownet_negative.txt`。
- 如果有完整 HowNet/知网词典，可直接替换上述文件，或放入 `positive.txt`、`negative.txt`、`正面情感词语（中文）.txt`、`负面情感词语（中文）.txt` 等文件名，程序会自动合并读取。
- 分析程序结合课程材料中的中文文本分类思路，使用 `jieba` 词级 TF-IDF、字级 2-4gram TF-IDF、情感词典计数/分数特征共同训练模型。字级 n-gram 借鉴了文本分类实验中“中文可按字建模”和 FastText bigram/trigram 的思想，更适合弹幕短文本和网络梗。

迭代学习说明：

- 每轮实验会生成 `results/实验名称/round_x/review_samples.csv`，数量约为本轮预测样本的8%，最多100条。
- 默认连续运行 4 轮：前 3 轮每轮分析后会在终端逐条询问待复核样本标签，最多 100 条；第 4 轮不再提问，作为最终结果。
- 已经人工标注过的弹幕不会再次进入待复核列表；人工标签优先级最高。
- 推荐直接按终端提示输入 `1`、`0`、`-1`；程序会自动写回 `review_samples.csv` 并进入下一轮。
- 如果你手动打开 CSV，也可以在 `review_label` 列填写 `1`、`0`、`-1`，分别表示正面、中性、负面；也兼容填写 `正面`、`中性`、`负面`。
- 下次运行 `python src/run_experiment.py` 时，程序会自动读取历史人工复核样本加入训练。
- 最终结果位于 `results/实验名称/final_round_4/` 和 `figures/实验名称/final_round_4/`。

也可以只运行分析脚本：

```bash
pip install -r requirements.txt
python src/train_analyze.py
```

运行后会自动生成：

- `results/model_metrics.csv`
- `results/danmu_predicted.csv`
- `results/partition_sentiment_stats.csv`
- `figures/model_metrics.png`
- `figures/partition_sentiment.png`
- `figures/keywords_top15.png`

## 汇报建议

按PPT顺序讲：研究意义 → 数据流程 → 特征模型 → 模型结果 → 分区差异 → 原因解释 → 总结创新。
