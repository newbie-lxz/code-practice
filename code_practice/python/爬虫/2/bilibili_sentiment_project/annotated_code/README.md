# 注释版代码说明

这个文件夹只用于阅读代码，正式运行仍然使用 `src/` 目录里的原始脚本。

读完可以直接删除整个 `annotated_code/` 文件夹，不会影响项目运行。

建议阅读顺序：

1. `run_experiment_annotated.py`：先看一键运行主流程。
2. `crawler_bilibili_annotated.py`：再看 B 站弹幕怎么爬。
3. `train_analyze_annotated.py`：重点看清洗、分词、情感词典、模型训练、预测和图表输出。
4. `make_sample_data_annotated.py`：最后看演示样例数据怎么生成。

正式运行命令仍然是：

```powershell
python src\run_experiment.py
```
