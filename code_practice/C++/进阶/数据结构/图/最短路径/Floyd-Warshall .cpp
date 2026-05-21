#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX / 2; // 避免加法溢出
//稠密+负权

// Floyd-Warshall 求解所有点对最短路径
void floydWarshall(vector<vector<int>>& dist, int V) {
    // 枚举中间点 k
    for (int k = 0; k < V; ++k) {
        // 枚举起点 i
        for (int i = 0; i < V; ++i) {
            // 枚举终点 j
            for (int j = 0; j < V; ++j) {
                // 若 i->k 或 k->j 不可达，跳过
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                // 更新最短路径
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    // 测试用例：4个顶点的图（含负权边，无负权环）
    int V = 4;
    // 初始化距离矩阵：dist[i][j] 表示 i 到 j 的初始距离
    vector<vector<int>> dist(V, vector<int>(V, INF));
    // 自环距离为0
    for (int i = 0; i < V; ++i) dist[i][i] = 0;
    // 手动添加边：u -> v，权值 w
    dist[0][1] = 2;
    dist[0][2] = 6;
    dist[1][2] = 3;
    dist[1][3] = 1;
    dist[2][3] = -2; // 负权边
    dist[3][1] = 1;

    // 运行 Floyd-Warshall
    floydWarshall(dist, V);

    // 输出结果
    cout << "=== Floyd-Warshall 所有点对最短路径 ===" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "起点 " << i << "：";
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) cout << "∞ ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    // 检测负权环（若任意点 i 的 dist[i][i] < 0，说明存在负权环）
    bool hasNegativeCycle = false;
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            break;
        }
    }
    cout << "是否存在负权环：" << (hasNegativeCycle ? "是" : "否") << endl;

    return 0;
}