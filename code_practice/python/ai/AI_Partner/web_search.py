from ddgs import DDGS
def search_web(query, max_results=5):
    try:
        results = DDGS(timeout=10).text(
            query,
            region="cn-zh",
            safesearch="moderate",
            max_results=max_results
        )

        if not results:
            return "", []

        search_content = ""
        sources = []

        for index, result in enumerate(results, start=1):
            title = result.get("title", "")
            url = result.get("href", "")
            body = result.get("body", "")

            search_content +=  f"""
                                    搜索结果 {index}

                                    标题：{title}

                                    网址：{url}

                                    摘要：{body}

                                """

            sources.append({
                "title": title,
                "url": url
            })

        return search_content, sources

    except Exception as e:
        print("联网搜索失败：", e)
        return "", []