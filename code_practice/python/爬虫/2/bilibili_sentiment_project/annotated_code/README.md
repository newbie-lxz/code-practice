# 注释版代码说明

本目录只用于阅读代码，正式运行使用 `src/` 目录中的 Notebook。

建议阅读顺序：

1. `run_experiment_annotated.ipynb`：理解四轮主动学习总流程。
2. `crawler_bilibili_annotated.ipynb`：理解 BV、cid、视频信息和弹幕采集。
3. `train_analyze_annotated.ipynb`：重点阅读清洗、特征、四模型、篇章分析和输出。
4. `make_sample_data_annotated.ipynb`：理解演示训练数据如何生成。

辅助说明：

- `lexicon说明.md`：词典如何加载和匹配。
- `分类规则说明.md`：模型与最终标签规则如何配合。

正式使用方法：

1. 用 VS Code 或 Jupyter 打开 `src/run_experiment.ipynb`。
2. 点击 `Run All / 全部运行`。
3. 按提示输入实验名称和两个 BV 号。

删除整个 `annotated_code/` 不会影响正式运行。
