#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
//稀疏+无负

typedef pair<int, int> PII; // 第一维：距离，第二维：顶点编号
const int INF = INT_MAX / 2;

// 单源 Dijkstra 算法
void dijkstra(int start, const vector<vector<PII>>& adj, vector<int>& dist) {
    int V = adj.size();
    dist.assign(V, INF);
    dist[start] = 0;
    // 优先队列：小顶堆（默认大顶堆，需加负号或指定比较器）
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        // 已找到更短路径，跳过
        if (d > dist[u]) continue;
        // 遍历邻接边
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    // 测试用例：4个顶点的稀疏无负权图
    int V = 4;
    // 邻接表：adj[u] 存储 (v, w) 表示 u->v 的边权为 w
    vector<vector<PII>> adj(V);
    adj[0].emplace_back(1, 2);
    adj[0].emplace_back(2, 6);
    adj[1].emplace_back(2, 3);
    adj[1].emplace_back(3, 1);
    adj[2].emplace_back(3, 2); // 无负权
    adj[3].emplace_back(1, 1);

    // n重 Dijkstra：遍历每个起点
    cout << "=== n重 Dijkstra 所有点对最短路径 ===" << endl;
    for (int start = 0; start < V; ++start) {
        vector<int> dist;
        dijkstra(start, adj, dist);
        cout << "起点 " << start << "：";
        for (int j = 0; j < V; ++j) {
            if (dist[j] == INF) cout << "∞ ";
            else cout << dist[j] << " ";
        }
        cout << endl;
    }

    return 0;
}