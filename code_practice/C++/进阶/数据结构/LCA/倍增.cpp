#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_LOG = 20; // 最多支持2^20 ≈ 1e6层的树
vector<vector<int>> tree;
vector<vector<int>> up; // up[k][u] = u向上跳2^k步的节点
vector<int> depth;

// 预处理up和depth
void dfs(int u, int fa) {
    up[0][u] = fa; // 2^0=1步，直接跳父节点
    depth[u] = (fa == -1) ? 0 : depth[fa] + 1;
    // 预处理2^1, 2^2,...步的跳转
    for (int k = 1; k < MAX_LOG; ++k) {
        if (up[k-1][u] != -1) {
            up[k][u] = up[k-1][up[k-1][u]];
        } else {
            up[k][u] = -1;
        }
    }
    // 递归处理子节点
    for (int v : tree[u]) {
        if (v != fa) {
            dfs(v, u);
        }
    }
}

// 把u向上跳d步
int jump(int u, int d) {
    for (int k = 0; k < MAX_LOG && d > 0; ++k) {
        if (d & (1 << k)) { // 若d的第k位为1，跳2^k步
            u = up[k][u];
            d -= (1 << k);
            if (u == -1) break;
        }
    }
    return u;
}

// 倍增法找LCA
int lca_binary_lift(int u, int v) {
    // 1. 让u成为深度更深的节点
    if (depth[u] < depth[v]) swap(u, v);
    // 2. 把u跳到和v同一深度
    u = jump(u, depth[u] - depth[v]);
    if (u == v) return u;
    // 3. 从大到小尝试跳，直到找到LCA
    for (int k = MAX_LOG - 1; k >= 0; --k) {
        if (up[k][u] != -1 && up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u]; // 最终u/v的父节点就是LCA
}

int main() {
    int n = 7;
    tree.resize(n);
    up.resize(MAX_LOG, vector<int>(n, -1));
    depth.resize(n);
    
    // 构建和之前一样的树
    tree[0].push_back(1);
    tree[1].push_back(0);
    tree[0].push_back(2);
    tree[2].push_back(0);
    tree[1].push_back(3);
    tree[3].push_back(1);
    tree[1].push_back(4);
    tree[4].push_back(1);
    tree[2].push_back(5);
    tree[5].push_back(2);
    tree[2].push_back(6);
    tree[6].push_back(2);
    
    // 预处理（根节点0的父节点是-1）
    dfs(0, -1);
    
    // 测试
    cout << "LCA(3,4) = " << lca_binary_lift(3,4) << endl; // 1
    cout << "LCA(3,5) = " << lca_binary_lift(3,5) << endl; // 0
    cout << "LCA(5,6) = " << lca_binary_lift(5,6) << endl; // 2
    return 0;
}