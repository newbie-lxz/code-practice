# AI_Partner

一个基于 Streamlit 的 AI 智能伴侣网页聊天项目。它通过 DeepSeek 的 OpenAI 兼容接口生成回复，并可选用 DuckDuckGo 搜索补充实时信息。

## 已实现功能

- 多轮聊天与流式回复。
- 自定义伴侣昵称和性格。
- 新建、加载、删除本地历史会话。
- 历史会话按最近使用时间排序。
- 可开启或关闭联网搜索；回答下方会展示搜索来源。
- 聊天记录只保存在本机的 `session_data/`，不会提交到仓库。

## 项目结构

```text
AI_Partner/
├── ai_partner_ai.py   # Streamlit 主程序：界面、会话管理、模型调用
├── web_search.py      # 联网搜索模块：调用 DDGS 并整理搜索结果
├── resource/
│   └── logo.png       # 页面 Logo
├── session_data/      # 本地聊天记录，运行后自动创建，不提交
├── .env               # 本机 API Key 配置，不提交
└── README.md
```

## 环境准备

建议使用 Python 3.10 或更高版本。在项目目录中安装依赖：

```bash
pip install streamlit openai python-dotenv ddgs
```

然后新建 `.env` 文件，并写入自己的 DeepSeek API Key：

```env
DEEPSEEK_KEY=请在这里填写你自己的密钥
```

`.env` 已被 Git 忽略，不能提交或分享真实密钥。

## 启动

在 `AI_Partner` 目录运行：

```bash
streamlit run ai_partner_ai.py
```

浏览器打开 Streamlit 给出的本地地址后，就可以开始对话。

## 文件说明

### `ai_partner_ai.py`

项目入口。负责创建 Streamlit 页面、维护聊天状态、保存与读取 JSON 历史记录、切换联网搜索、调用 DeepSeek 模型并流式显示回答。

### `web_search.py`

将用户问题交给 `ddgs` 搜索，提取标题、链接和摘要，整理后提供给主程序作为模型的补充上下文，同时返回可展示的来源链接。

### `session_data/`

每个会话以时间戳 JSON 文件保存，包含昵称、性格和聊天消息。这个目录属于个人本地数据，已在 `.gitignore` 中排除。

## 注意事项

- API Key 仅保存在本机 `.env`，请不要写入代码、截图或提交记录。
- 每次请求会发送当前完整对话作为上下文；对话很长时会增加 Token 消耗。
- 联网搜索依赖外部搜索服务，网络不可用时会自动返回空结果，聊天功能仍可继续使用。
