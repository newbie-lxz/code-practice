# 人工反馈说明

一键实验会在 `results/实验名称/review_samples.csv` 中生成待复核样本。

待复核样本约占本轮预测弹幕的 8%，优先选择模型低置信度、词典与模型冲突、以及正面/负面/中性代表样本。

把 `review_label` 列填写为以下任意一种即可：

- `1` 或 `正面`
- `0` 或 `中性`
- `-1` 或 `负面`

保存后再次运行 `python src/run_experiment.py`，程序会自动读取历史 `review_samples.csv` 中已填写的人工标签，并加入下一轮训练。

也可以把人工标注 CSV 放在本目录下，要求至少包含：

```text
text,review_label
```
