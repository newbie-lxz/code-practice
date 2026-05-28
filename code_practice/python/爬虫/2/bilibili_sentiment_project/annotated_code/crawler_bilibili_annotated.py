# -*- coding: utf-8 -*-
"""
注释阅读版：crawler_bilibili.py

负责访问 B 站接口，先用 BV 号拿 cid，再根据 cid 拉取 XML 弹幕，最后保存 CSV。

注意：
1. 本文件只用于阅读理解，正式运行请使用 src 目录里的原文件。
2. 每段代码前面的 '# 注释：' 是对下一行或下一小段代码的解释。
3. 读完可以直接删除整个 annotated_code 文件夹，不影响项目。
"""

# 注释：这里是文档字符串，用自然语言说明当前文件或函数的用途。
"""
B站弹幕采集脚本：根据 BV 号获取 cid，再拉取 XML 弹幕。
说明：B站接口和风控策略可能变化；若请求失败，请在浏览器登录后复制 Cookie 到 headers。
输出：data/raw_bilibili_danmu.csv
"""
# 注释：导入 csv，供后续代码调用。
import csv
# 注释：导入 time，供后续代码调用。
import time
# 注释：导入 xml.etree.ElementTree as ET，供后续代码调用。
import xml.etree.ElementTree as ET
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from pathlib import Path
# 注释：从指定模块导入需要的类或函数，避免后面写很长的模块路径。
from typing import List, Dict, Optional

# 注释：导入 requests，供后续代码调用。
import requests

# 注释：定位项目根目录。
ROOT = Path(__file__).resolve().parents[1]
# 注释：设置默认输出文件路径。
OUT = ROOT / "data" / "raw_bilibili_danmu.csv"

# 注释：设置请求头，模拟浏览器访问 B 站。
HEADERS = {
    # 注释：这是列表、字典或函数参数中的一项。
    "User-Agent": "Mozilla/5.0",
    # 注释：这是列表、字典或函数参数中的一项。
    "Referer": "https://www.bilibili.com/",
    # 如遇到403/风控，可将浏览器 Cookie 填在这里：
    # "Cookie": "SESSDATA=...; bili_jct=...;"
# 注释：结束上面开启的列表、字典、元组或函数调用。
}

# 示例：把每个分区准备若干 BV 号。真实提交时替换为你们选定的视频。
# 注释：默认示例视频列表，正式运行时通常由 run_experiment.py 动态传入。
VIDEOS = [
    # 注释：这是列表、字典或函数参数中的一项。
    {"partition": "学习区", "bvid": "BV1BiDaB1EEN"},
    # 注释：这是列表、字典或函数参数中的一项。
    {"partition": "生活区", "bvid": "BV1MDA6zHEFE"},
# 注释：结束上面开启的列表、字典、元组或函数调用。
]


# 注释：访问 B 站视频信息接口，返回 cid、标题、播放量、点赞数等元数据。
def get_video_info(bvid: str) -> Dict[str, str]:
    # 注释：给变量 url 赋值，供后续步骤使用。
    url = "https://api.bilibili.com/x/web-interface/view"
    # 注释：发送 HTTP GET 请求访问 B 站接口。
    r = requests.get(url, params={"bvid": bvid}, headers=HEADERS, timeout=15)
    # 注释：检查 HTTP 请求是否成功；失败时抛出异常。
    r.raise_for_status()
    # 注释：给变量 data 赋值，供后续步骤使用。
    data = r.json()
    # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
    if data.get("code") != 0:
        # 注释：主动抛出错误，让调用者知道当前流程无法继续。
        raise RuntimeError(f"获取 cid 失败：{bvid}, 返回={data}")
    # 注释：给变量 info 赋值，供后续步骤使用。
    info = data["data"]
    # 注释：给变量 stat 赋值，供后续步骤使用。
    stat = info.get("stat", {})
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return {
        # 注释：这是列表、字典或函数参数中的一项。
        "cid": int(info["cid"]),
        # 注释：这是列表、字典或函数参数中的一项。
        "title": info.get("title", ""),
        # 注释：这是列表、字典或函数参数中的一项。
        "view_count": stat.get("view", 0),
        # 注释：这是列表、字典或函数参数中的一项。
        "like_count": stat.get("like", 0),
        # 注释：这是列表、字典或函数参数中的一项。
        "coin_count": stat.get("coin", 0),
        # 注释：这是列表、字典或函数参数中的一项。
        "favorite_count": stat.get("favorite", 0),
        # 注释：这是列表、字典或函数参数中的一项。
        "reply_count": stat.get("reply", 0),
        # 注释：这是列表、字典或函数参数中的一项。
        "danmaku_count": stat.get("danmaku", 0),
    # 注释：结束上面开启的列表、字典、元组或函数调用。
    }


# 注释：只取视频 cid，保留给旧版调用方式兼容。
def get_cid(bvid: str) -> int:
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return int(get_video_info(bvid)["cid"])


# 注释：根据 cid 请求 XML 弹幕接口，并解析出每条弹幕文本。
def get_danmu(cid: int) -> List[str]:
    # 注释：给变量 url 赋值，供后续步骤使用。
    url = "https://api.bilibili.com/x/v1/dm/list.so"
    # 注释：发送 HTTP GET 请求访问 B 站接口。
    r = requests.get(url, params={"oid": cid}, headers=HEADERS, timeout=20)
    # 注释：检查 HTTP 请求是否成功；失败时抛出异常。
    r.raise_for_status()
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    r.encoding = "utf-8"
    # 注释：把 XML 文本解析为可遍历的 XML 树。
    root = ET.fromstring(r.text)
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return [node.text.strip() for node in root.findall("d") if node.text and node.text.strip()]


# 注释：批量爬取多个 BV 的弹幕，统一整理成 CSV 行。
def crawl(
    # 注释：这是列表、字典或函数参数中的一项。
    videos: Optional[List[Dict[str, str]]] = None,
    # 注释：这是列表、字典或函数参数中的一项。
    out: Path = OUT,
    # 注释：这是列表、字典或函数参数中的一项。
    max_per_video: Optional[int] = None,
# 注释：结束上面开启的列表、字典、元组或函数调用。
) -> List[Dict[str, str]]:
    # 注释：给变量 videos 赋值，供后续步骤使用。
    videos = videos or VIDEOS
    # 注释：给变量 out 赋值，供后续步骤使用。
    out = Path(out)
    # 注释：创建目录；parents=True 时会自动创建不存在的上级目录。
    out.parent.mkdir(parents=True, exist_ok=True)
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    rows: List[Dict[str, str]] = []
    # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
    for item in videos:
        # 注释：给变量 bvid 赋值，供后续步骤使用。
        bvid = item["bvid"]
        # 注释：给变量 partition 赋值，供后续步骤使用。
        partition = item["partition"]
        # 注释：异常保护：尝试执行可能失败的代码。
        try:
            # 注释：给变量 video_info 赋值，供后续步骤使用。
            video_info = get_video_info(bvid)
            # 注释：给变量 texts 赋值，供后续步骤使用。
            texts = get_danmu(video_info["cid"])
            # 注释：条件判断：只有条件成立时，才执行下面缩进的代码块。
            if max_per_video:
                # 注释：给变量 texts 赋值，供后续步骤使用。
                texts = texts[:max_per_video]
            # 注释：循环处理一组数据，逐个取出元素执行下面的逻辑。
            for text in texts:
                # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
                rows.append({
                    # 注释：这是列表、字典或函数参数中的一项。
                    "partition": partition,
                    # 注释：这是列表、字典或函数参数中的一项。
                    "bvid": bvid,
                    # 注释：这是列表、字典或函数参数中的一项。
                    "title": video_info["title"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "view_count": video_info["view_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "like_count": video_info["like_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "coin_count": video_info["coin_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "favorite_count": video_info["favorite_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "reply_count": video_info["reply_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "danmaku_count": video_info["danmaku_count"],
                    # 注释：这是列表、字典或函数参数中的一项。
                    "text": text,
                # 注释：结束上面开启的列表、字典、元组或函数调用。
                })
            # 注释：向终端输出提示信息，方便观察程序运行进度。
            print(f"{partition} {bvid}: {len(texts)} 条")
            # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
            time.sleep(1)
        # 注释：异常处理：上面的 try 出错时，执行这里的补救逻辑。
        except Exception as e:
            # 注释：向终端输出提示信息，方便观察程序运行进度。
            print(f"跳过 {bvid}: {e}")

    # 注释：使用上下文管理器打开资源，代码块结束后自动关闭。
    with out.open("w", newline="", encoding="utf-8-sig") as f:
        # 注释：给变量 writer 赋值，供后续步骤使用。
        writer = csv.DictWriter(f, fieldnames=[
            # 注释：这是列表、字典或函数参数中的一项。
            "partition", "bvid", "title", "view_count", "like_count",
            # 注释：这是列表、字典或函数参数中的一项。
            "coin_count", "favorite_count", "reply_count", "danmaku_count", "text",
        # 注释：结束上面开启的列表、字典、元组或函数调用。
        ])
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        writer.writeheader()
        # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
        writer.writerows(rows)
    # 注释：向终端输出提示信息，方便观察程序运行进度。
    print(f"已保存：{out}, 共 {len(rows)} 条")
    # 注释：返回当前函数的计算结果，交给调用它的代码继续使用。
    return rows


# 注释：判断当前文件是否被直接运行；直接运行时才启动主流程。
if __name__ == "__main__":
    # 注释：执行这一行 Python 代码，是当前流程中的一个具体步骤。
    crawl()
