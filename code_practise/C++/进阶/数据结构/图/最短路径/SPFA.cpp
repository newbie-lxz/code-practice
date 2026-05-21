#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;

/**
 * @brief SPFA 算法（含负权环检测）
 * @param n 顶点数量
 * @param adj 邻接表（adj[u] 存储 (v, w)）
 * @param start 源点
 * @param has_negative_cycle 输出参数：是否存在从源点可达的负权环
 * @return 源点到各顶点的最短距离数组（若存在负权环，结果无意义）
 */
vector<int> spfa(int n, const vector<vector<pair<int, int>>>& adj, int start, bool& has_negative_cycle) {
    // 1. 初始化距离数组
    vector<int> dist(n, INF);
    dist[start] = 0;

    // 辅助数组：in_queue[u] 表示 u 是否在队列中（防止重复入队）
    vector<bool> in_queue(n, false);
    // 辅助数组：cnt[u] 统计 u 入队次数（检测负权环）
    vector<int> cnt(n, 0);

    // 2. 初始化队列，源点入队
    queue<int> q;
    q.push(start);
    in_queue[start] = true;
    cnt[start] = 1;

    // 3. 核心松弛过程
    has_negative_cycle = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false; // 出队，标记为不在队列

        // 遍历 u 的所有邻边
        for (auto [v, w] : adj[u]) {
            // 松弛操作
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                // 若 v 不在队列中，入队并更新统计
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                    cnt[v]++;

                    // 检测负权环：入队次数超过顶点数，说明存在负权环
                    if (cnt[v] > n) {
                        has_negative_cycle = true;
                        return dist; // 提前退出，结果无意义
                    }
                }
            }
        }
    }

    return dist;
}

// 测试用例 1：无负权环（含负权边）
void test_spfa_normal() {
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    adj[0].emplace_back(1, 6);
    adj[0].emplace_back(2, 7);
    adj[1].emplace_back(2, 8);
    adj[1].emplace_back(3, -4);
    adj[1].emplace_back(4, 5);
    adj[2].emplace_back(3, 9);
    adj[2].emplace_back(4, -3);
    adj[3].emplace_back(1, 2);
    adj[4].emplace_back(3, 7);
    adj[4].emplace_back(0, 2);

    int start = 0;
    bool has_cycle;
    vector<int> dist = spfa(n, adj, start, has_cycle);

    cout << "\nSPFA 算法（无负权环）结果：" << endl;
    cout << "是否存在负权环：" << (has_cycle ? "是" : "否") << endl;
    cout << "源点 " << start << " 到各顶点的最短距离：" << endl;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << start << " → " << i << ": 不可达" << endl;
        } else {
            cout << start << " → " << i << ": " << dist[i] << endl;
        }
    }
}

// 测试用例 2：含负权环
void test_spfa_cycle() {
    int n = 3;
    vector<vector<pair<int, int>>> adj(n);
    // 0→1 (1), 1→2 (2), 2→0 (-4) → 形成负权环（总权重 -1）
    adj[0].emplace_back(1, 1);
    adj[1].emplace_back(2, 2);
    adj[2].emplace_back(0, -4);
    adj[0].emplace_back(2, 5);

    int start = 0;
    bool has_cycle;
    vector<int> dist = spfa(n, adj, start, has_cycle);

    cout << "\nSPFA 算法（含负权环）结果：" << endl;
    cout << "是否存在负权环：" << (has_cycle ? "是" : "否") << endl;
    cout << "（注：负权环存在时，最短距离无意义）" << endl;
}

int main() {
    test_spfa_normal(); // 测试无负权环场景
    test_spfa_cycle();  // 测试含负权环场景
    return 0;
}