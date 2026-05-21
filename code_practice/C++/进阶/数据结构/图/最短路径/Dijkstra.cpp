#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f; // 定义无穷大

/**
 * @brief 堆优化版 Dijkstra 算法
 * @param n 顶点数量
 * @param adj 邻接表（adj[u] 存储 (v, w)，表示 u→v 权重为 w）
 * @param start 源点
 * @return 源点到各顶点的最短距离数组
 */
vector<int> dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int start) {
    // 1. 初始化距离数组：源点为 0，其余为 INF
    vector<int> dist(n, INF);
    dist[start] = 0;

    // 2. 优先队列（小根堆）：存储 (当前距离, 节点)，默认大根堆，故用 greater 转为小根堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    // 3. 核心贪心过程
    while (!pq.empty()) {
        auto [d, u] = pq.top(); // 当前距离最小的节点（C++17 结构化绑定，低版本可拆分为：int d = pq.top().first; int u = pq.top().second;）
        pq.pop();

        // 剪枝：若当前距离大于已记录的最短距离，跳过（该节点已处理过）
        if (d > dist[u]) continue;

        // 遍历 u 的所有邻边，松弛操作
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v); // 更新后入队（允许重复入队，靠剪枝过滤）
            }
        }
    }

    return dist;
}

// 测试用例
int main() {
    // 构建图：顶点数 5，邻接表形式
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    // 边列表：(u, v, w) → 对应 adj[u].emplace_back(v, w)
    adj[0].emplace_back(1, 6);
    adj[0].emplace_back(2, 7);
    adj[1].emplace_back(2, 8);
    adj[1].emplace_back(3, -4); // 注意：Dijkstra 不支持负权边，此处仅为对比，实际运行结果可能错误
    adj[1].emplace_back(4, 5);
    adj[2].emplace_back(3, 9);
    adj[2].emplace_back(4, -3);
    adj[3].emplace_back(1, 2);
    adj[4].emplace_back(3, 7);
    adj[4].emplace_back(0, 2);

    int start = 0;
    vector<int> dist = dijkstra(n, adj, start);

    cout << "Dijkstra 算法（堆优化版）结果：" << endl;
    cout << "源点 " << start << " 到各顶点的最短距离：" << endl;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << start << " → " << i << ": 不可达" << endl;
        } else {
            cout << start << " → " << i << ": " << dist[i] << endl;
        }
    }

    return 0;
}