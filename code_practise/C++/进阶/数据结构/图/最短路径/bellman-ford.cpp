#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 定义无穷大（选择 0x3f3f3f3f，避免溢出且可批量初始化）
const int INF = 0x3f3f3f3f;

// 边的结构体：u -> v，权重为 w
struct Edge {
    int u, v, w;
    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
};

/**
 * @brief 未优化版 Bellman-Ford 算法
 * @param n 顶点数量（顶点编号从 0 开始）
 * @param edges 所有边的列表
 * @param start 源点编号
 * @param has_negative_cycle 输出参数：是否存在从源点可达的负权环
 * @return 源点到各顶点的最短距离数组（若存在负权环，结果无意义）
 */
vector<int> bellman_ford_unoptimized(int n, const vector<Edge>& edges, int start, bool& has_negative_cycle) {
    // 1. 初始化距离数组：源点距离为 0，其余为 INF
    vector<int> dist(n, INF);
    dist[start] = 0;

    // 2. 严格执行 n-1 轮松弛（未优化：不提前终止）
    for (int i = 0; i < n - 1; ++i) { // 共 n-1 轮
        // 每一轮遍历所有边，执行松弛操作
        for (const Edge& e : edges) {
            int u = e.u;
            int v = e.v;
            int w = e.w;
            // 仅当 u 可达（dist[u] 不是 INF）时，才尝试松弛 v
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // 3. 检测负权环：遍历所有边，若仍能松弛则存在负权环
    has_negative_cycle = false;
    for (const Edge& e : edges) {
        int u = e.u;
        int v = e.v;
        int w = e.w;
        if (dist[u] != INF && dist[v] > dist[u] + w) {
            has_negative_cycle = true;
            break; // 找到负权环，直接退出检测
        }
    }

    return dist;
}

// 测试用例 1：无负权环（含负权边）
void test_normal() {
    // 顶点数 5，边列表（与之前示例一致）
    int n = 5;
    vector<Edge> edges = {
        Edge(0, 1, 6),
        Edge(0, 2, 7),
        Edge(1, 2, 8),
        Edge(1, 3, -4),
        Edge(1, 4, 5),
        Edge(2, 3, 9),
        Edge(2, 4, -3),
        Edge(3, 1, 2),
        Edge(4, 3, 7),
        Edge(4, 0, 2)
    };
    int start = 0;
    bool has_cycle;

    vector<int> dist = bellman_ford_unoptimized(n, edges, start, has_cycle);

    cout << "===== 测试用例 1：无负权环 =====" << endl;
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
void test_negative_cycle() {
    // 顶点数 3，边列表（0→1→2→0 形成负权环：1+2-4=-1）
    int n = 3;
    vector<Edge> edges = {
        Edge(0, 1, 1),
        Edge(1, 2, 2),
        Edge(2, 0, -4),
        Edge(0, 2, 5)
    };
    int start = 0;
    bool has_cycle;

    vector<int> dist = bellman_ford_unoptimized(n, edges, start, has_cycle);

    cout << "\n===== 测试用例 2：含负权环 =====" << endl;
    cout << "是否存在负权环：" << (has_cycle ? "是" : "否") << endl;
    cout << "注：负权环存在时，最短距离无实际意义" << endl;
}

int main() {
    test_normal();       // 测试无负权环场景
    test_negative_cycle();// 测试含负权环场景
    return 0;
}