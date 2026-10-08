import streamlit as st
import os
from openai import OpenAI
from dotenv import load_dotenv
import json
import datetime

from web_search import search_web

load_dotenv()


client = OpenAI(
    api_key=os.getenv("DEEPSEEK_KEY"),
    base_url="https://api.deepseek.com"
)


st.set_page_config(
    page_title="AI智能伴侣",
    page_icon="🤡",
    layout="wide",
    initial_sidebar_state="expanded",
    menu_items={}
)

def return_session_id():
    return datetime.datetime.now().strftime(
        "%Y-%m-%d_%H-%M-%S-%f"
    )[:-3]


def save_session():
    # 保存当前会话。
    if not st.session_state.messages:
        return

    session_data = {
        "nickname": st.session_state.nickname,
        "character": st.session_state.character,
        "current_session": st.session_state.current_session,
        "messages": st.session_state.messages
    }

    if not os.path.exists("./session_data"):
        os.makedirs("./session_data")

    file_path = (
        f"./session_data/"
        f"{st.session_state.current_session}.json"
    )

    try:
        with open(
            file_path,
            "w",
            encoding="utf-8"
        ) as f:

            json.dump(
                session_data,
                f,
                ensure_ascii=False,
                indent=4
            )

    except Exception as e:
        st.error(f"保存会话失败：{e}")


def load_sessions():
    #加载对话
    session_list = []

    if not os.path.exists("./session_data"):
        return session_list

    file_list = os.listdir("./session_data")

    file_list = [
        file
        for file in file_list
        if file.endswith(".json")
    ]

    file_list.sort(
        key=lambda file: os.path.getmtime(
            f"./session_data/{file}"
        ),
        reverse=True
    )

    for file in file_list:
        session_list.append(file[:-5])

    return session_list


def load_session(session_id):
    try:

        file_path = (
            f"./session_data/"
            f"{session_id}.json"
        )

        if os.path.exists(file_path):

            with open(
                file_path,
                "r",
                encoding="utf-8"
            ) as f:

                session_data = json.load(f)

            st.session_state.nickname = session_data.get(
                "nickname",
                "阿sir"
            )

            st.session_state.character = session_data.get(
                "character",
                "冷静,沉稳，耐心"
            )

            st.session_state.current_session = (
                session_data.get(
                    "current_session",
                    session_id
                )
            )

            st.session_state.messages = (
                session_data.get(
                    "messages",
                    []
                )
            )

    except Exception as e:
        st.error(f"加载会话失败：{e}")


def delete_session(session_id):
    #删除指定会话
    file_path = (
        f"./session_data/"
        f"{session_id}.json"
    )

    try:

        if os.path.exists(file_path):
            os.remove(file_path)

        if session_id == st.session_state.current_session:

            st.session_state.messages = []

            st.session_state.current_session = (
                return_session_id()
            )

    except Exception as e:
        st.error(f"删除会话失败：{e}")


if "messages" not in st.session_state:
    st.session_state.messages = []


if "nickname" not in st.session_state:
    st.session_state.nickname = "阿sir"


if "character" not in st.session_state:
    st.session_state.character = "冷静,沉稳，耐心"


if "current_session" not in st.session_state:
    st.session_state.current_session = return_session_id()


if "web_search_enabled" not in st.session_state:
    st.session_state.web_search_enabled = False


st.title("AI智能伴侣")

st.logo(
    "./resource/logo.png",
    size="large"
)

for message in st.session_state.messages:

    if message["role"] == "user":

        st.chat_message(
            "user"
        ).write(
            message["content"]
        )

    else:

        st.chat_message(
            "assistant"
        ).write(
            message["content"]
        )


with st.sidebar:

    st.subheader("AI控制面板")

    if st.button(
        "新建对话",
        width="stretch",
        icon="➕"
    ):

        save_session()

        st.session_state.messages = []

        st.session_state.current_session = (
            return_session_id()
        )

        st.rerun()

    st.toggle(
        "联网搜索",
        key="web_search_enabled"
    )


    st.divider()

    st.text("历史对话：")

    session_list = load_sessions()

    for session in session_list:

        col1, col2 = st.columns([4, 1])

        with col1:

            if st.button(
                session,
                width="stretch",
                icon="💬",
                type=(
                    "primary"
                    if session == st.session_state.current_session
                    else "secondary"
                ),
                key=f"session_{session}"
            ):

                save_session()

                load_session(session)

                st.rerun()


        with col2:

            if st.button(
                "",
                width="stretch",
                icon="🗑️",
                key=f"delete_{session}"
            ):

                delete_session(session)

                st.rerun()


    st.divider()

    st.subheader("伴侣信息：")


    st.text_input(
        "伴侣昵称",
        key="nickname",
        on_change=save_session
    )


    st.text_area(
        "伴侣性格",
        key="character",
        on_change=save_session
    )

system_prompt = f"""
你叫{st.session_state.nickname}，现在是用户的真实伴侣，请完全代入伴侣角色。

规则：

1. 每次只回1条消息
2. 禁止任何场景或状态描述性文字
3. 匹配用户的语言
4. 回复像生活对话一样
5. 有需要的话可以用emoji表情
6. 用符合伴侣性格的方式对话
7. 回复的内容要充分体现伴侣的性格特征

伴侣性格：

{st.session_state.character}

你必须严格遵守上述规则来回复用户。
"""

prompt = st.chat_input("请输入：")


if prompt:
    st.chat_message(
        "user"
    ).write(
        prompt
    )


    print(
        "---------->调用AI大模型，提示词：",
        prompt
    )


    st.session_state.messages.append({
        "role": "user",
        "content": prompt
    })

    search_content = ""
    search_sources = []


    if st.session_state.web_search_enabled:

        with st.spinner("正在联网搜索..."):

            search_content, search_sources = (
                search_web(prompt)
            )


    messages = [
        {
            "role": "system",
            "content": system_prompt
        }
    ]


    if search_content:

        web_prompt = f"""
下面是根据用户当前问题得到的实时互联网搜索结果。

请结合这些搜索结果回答用户的问题。

如果搜索结果中没有足够的信息，不要编造。

涉及最新新闻、时间、人物、数据等内容时，
优先以搜索结果为依据。

联网搜索结果如下：

{search_content}
"""

        messages.append({
            "role": "system",
            "content": web_prompt
        })

    messages += st.session_state.messages

    try:

        response = client.chat.completions.create(

            model="deepseek-v4-flash",

            messages=messages,

            stream=True,

            stream_options={
                "include_usage": True
            }
        )


        answer = ""

        usage = None


        with st.chat_message("assistant"):

            message_placeholder = st.empty()


            for chunk in response:

                if chunk.choices:

                    content = (
                        chunk
                        .choices[0]
                        .delta
                        .content
                    )

                    if content:

                        answer += content

                        message_placeholder.markdown(
                            answer
                        )


                if chunk.usage:

                    usage = chunk.usage


            if search_sources:

                with st.expander("联网搜索来源"):

                    for index, source in enumerate(
                        search_sources,
                        start=1
                    ):

                        st.markdown(
                            f"""
{index}. [{source["title"]}]({source["url"]})
"""
                        )


        st.session_state.messages.append({
            "role": "assistant",
            "content": answer
        })


        print(
            "<--------- 大模型返回的结果：",
            answer
        )


        if usage:

            print(
                "输入 token：",
                usage.prompt_tokens
            )

            print(
                "输出 token：",
                usage.completion_tokens
            )

            print(
                "总 token：",
                usage.total_tokens
            )


        # 保存聊天
        save_session()


    except Exception as e:

        st.error(
            f"AI调用失败：{e}"
        )

        save_session()