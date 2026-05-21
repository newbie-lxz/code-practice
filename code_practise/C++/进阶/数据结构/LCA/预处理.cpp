#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // 包含iota
using namespace std;

// 并查集（复用你之前的代码）
class UnionFind {
public:
    vector<int> parent;
    int n;
    UnionFind(int _n): n(_n), parent(_n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int findset(int x) {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    void unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x != y) parent[y] = x;
    }
};

vector<vector<int>> tree;
vector<vector<pair<int, int>>> queries; // queries[u] = {(v, idx)}：u和v的查询，编号为idx
vector<int> ans; // 存储每个查询的答案
vector<bool> visited;
UnionFind* uf;

// Tarjan离线LCA
void tarjan(int u, int fa) {
    visited[u] = true;
    // 处理所有和u相关的查询
    for (auto& q : queries[u]) {
        int v = q.first, idx = q.second;
        if (visited[v]) {
            ans[idx] = uf->findset(v);
        }
    }
    // 递归处理子节点
    for (int v : tree[u]) {
        if (v != fa && !visited[v]) {
            tarjan(v, u);
            uf->unite(u, v); // 子节点遍历完，合并到父节点
        }
    }
}

int main() {
    int n = 7, q = 3; // 3个查询
    tree.resize(n);
    queries.resize(n);
    ans.resize(q);
    visited.resize(n, false);
    uf = new UnionFind(n);
    
    // 构建树（同前）
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
    
    // 定义查询：(3,4)、(3,5)、(5,6)，编号0/1/2
    queries[3].emplace_back(4, 0);
    queries[4].emplace_back(3, 0); // 双向存储
    queries[3].emplace_back(5, 1);
    queries[5].emplace_back(3, 1);
    queries[5].emplace_back(6, 2);
    queries[6].emplace_back(5, 2);
    
    // 执行Tarjan（根节点0）
    tarjan(0, -1);
    
    // 输出结果
    cout << "查询0(3,4)的LCA：" << ans[0] << endl; // 1
    cout << "查询1(3,5)的LCA：" << ans[1] << endl; // 0
    cout << "查询2(5,6)的LCA：" << ans[2] << endl; // 2
    
    delete uf;
    return 0;
}