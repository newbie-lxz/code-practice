#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> PII;
const int INF = INT_MAX / 2;

// Bellman-Ford 算法：计算虚拟源点到所有点的最短路径（用于重赋权）
bool bellmanFord(int V, const vector<vector<PII>>& adj, vector<int>& h) {
    h.assign(V, INF);
    h[V-1] = 0; // 虚拟源点为最后一个顶点（编号 V-1）

    // 松弛 V-1 次
    for (int i = 0; i < V-1; ++i) {
        bool updated = false;
        // 遍历所有边（含虚拟源点的边）
        for (int u = 0; u < V; ++u) {
            if (h[u] == INF) continue;
            for (auto [v, w] : adj[u]) {
                if (h[v] > h[u] + w) {
                    h[v] = h[u] + w;
                    updated = true;
                }
            }
        }
        if (!updated) break; // 无更新，提前退出
    }

    // 检测负权环：若还能松弛，说明存在负权环
    for (int u = 0; u < V; ++u) {
        if (h[u] == INF) continue;
        for (auto [v, w] : adj[u]) {
            if (h[v] > h[u] + w) {
                return false; // 存在负权环
            }
        }
    }
    return true;
}

// 单源 Dijkstra（重赋权后的图）
void dijkstraJohnson(int start, const vector<vector<PII>>& adj, const vector<int>& h, vector<int>& dist) {
    int V = adj.size() - 1; // 排除虚拟源点
    dist.assign(V, INF);
    dist[start] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            // 重赋权后的边权：w' = w + h[u] - h[v]
            int new_w = w + h[u] - h[v];
            if (dist[v] > dist[u] + new_w) {
                dist[v] = dist[u] + new_w;
                pq.push({dist[v], v});
            }
        }
    }

    // 还原为原权值的最短路径：dist[i] = dist[i] - h[start] + h[i]
    for (int i = 0; i < V; ++i) {
        if (dist[i] != INF) {
            dist[i] = dist[i] - h[start] + h[i];
        }
    }
}

// Johnson 主算法
void johnson(vector<vector<PII>>& adj, int V) {
    // 步骤1：添加虚拟源点（编号 V），向所有顶点连权值为0的边
    adj.resize(V+1);
    for (int i = 0; i < V; ++i) {
        adj[V].emplace_back(i, 0);
    }

    // 步骤2：Bellman-Ford 计算 h[v]
    vector<int> h;
    if (!bellmanFord(V+1, adj, h)) {
        cout << "图中存在负权环，无法计算最短路径！" << endl;
        return;
    }

    // 步骤3：n重 Dijkstra 计算所有点对最短路径
    cout << "=== Johnson 所有点对最短路径 ===" << endl;
    for (int start = 0; start < V; ++start) {
        vector<int> dist;
        dijkstraJohnson(start, adj, h, dist);
        cout << "起点 " << start << "：";
        for (int j = 0; j < V; ++j) {
            if (dist[j] == INF) cout << "∞ ";
            else cout << dist[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 测试用例：4个顶点的稀疏图（含负权边）
    int V = 4;
    vector<vector<PII>> adj(V);
    adj[0].emplace_back(1, 2);
    adj[0].emplace_back(2, 6);
    adj[1].emplace_back(2, 3);
    adj[1].emplace_back(3, 1);
    adj[2].emplace_back(3, -2); // 负权边
    adj[3].emplace_back(1, 1);

    // 运行 Johnson 算法
    johnson(adj, V);

    return 0;
}