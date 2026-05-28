"""
B站弹幕采集脚本：根据 BV 号获取 cid，再拉取 XML 弹幕。
说明：B站接口和风控策略可能变化；若请求失败，请在浏览器登录后复制 Cookie 到 headers。
输出：data/raw_bilibili_danmu.csv
"""
import csv
import time
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import List, Dict, Optional

import requests

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "data" / "raw_bilibili_danmu.csv"

HEADERS = {
    "User-Agent": "Mozilla/5.0",
    "Referer": "https://www.bilibili.com/",
    # 如遇到403/风控，可将浏览器 Cookie 填在这里：
    # "Cookie": "SESSDATA=...; bili_jct=...;"
}

# 示例：把每个分区准备若干 BV 号。真实提交时替换为你们选定的视频。
VIDEOS = [
    {"partition": "学习区", "bvid": "BV1BiDaB1EEN"},
    {"partition": "生活区", "bvid": "BV1MDA6zHEFE"},
]


def get_video_info(bvid: str) -> Dict[str, str]:
    url = "https://api.bilibili.com/x/web-interface/view"
    r = requests.get(url, params={"bvid": bvid}, headers=HEADERS, timeout=15)
    r.raise_for_status()
    data = r.json()
    if data.get("code") != 0:
        raise RuntimeError(f"获取 cid 失败：{bvid}, 返回={data}")
    info = data["data"]
    stat = info.get("stat", {})
    return {
        "cid": int(info["cid"]),
        "title": info.get("title", ""),
        "view_count": stat.get("view", 0),
        "like_count": stat.get("like", 0),
        "coin_count": stat.get("coin", 0),
        "favorite_count": stat.get("favorite", 0),
        "reply_count": stat.get("reply", 0),
        "danmaku_count": stat.get("danmaku", 0),
    }


def get_cid(bvid: str) -> int:
    return int(get_video_info(bvid)["cid"])


def get_danmu(cid: int) -> List[str]:
    url = "https://api.bilibili.com/x/v1/dm/list.so"
    r = requests.get(url, params={"oid": cid}, headers=HEADERS, timeout=20)
    r.raise_for_status()
    r.encoding = "utf-8"
    root = ET.fromstring(r.text)
    return [node.text.strip() for node in root.findall("d") if node.text and node.text.strip()]


def crawl(
    videos: Optional[List[Dict[str, str]]] = None,
    out: Path = OUT,
    max_per_video: Optional[int] = None,
) -> List[Dict[str, str]]:
    videos = videos or VIDEOS
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)
    rows: List[Dict[str, str]] = []
    for item in videos:
        bvid = item["bvid"]
        partition = item["partition"]
        try:
            video_info = get_video_info(bvid)
            texts = get_danmu(video_info["cid"])
            if max_per_video:
                texts = texts[:max_per_video]
            for text in texts:
                rows.append({
                    "partition": partition,
                    "bvid": bvid,
                    "title": video_info["title"],
                    "view_count": video_info["view_count"],
                    "like_count": video_info["like_count"],
                    "coin_count": video_info["coin_count"],
                    "favorite_count": video_info["favorite_count"],
                    "reply_count": video_info["reply_count"],
                    "danmaku_count": video_info["danmaku_count"],
                    "text": text,
                })
            print(f"{partition} {bvid}: {len(texts)} 条")
            time.sleep(1)
        except Exception as e:
            print(f"跳过 {bvid}: {e}")

    with out.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=[
            "partition", "bvid", "title", "view_count", "like_count",
            "coin_count", "favorite_count", "reply_count", "danmaku_count", "text",
        ])
        writer.writeheader()
        writer.writerows(rows)
    print(f"已保存：{out}, 共 {len(rows)} 条")
    return rows


if __name__ == "__main__":
    crawl()
