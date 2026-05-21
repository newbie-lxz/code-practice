#include <vector>
#include <algorithm>
#include <unordered_set>  // 需包含set头文件
#include <numeric>
using namespace std;

class UF {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UF(int size) {
        parent.resize(size);
        rank.resize(size, 1);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // 修正后的number()函数：统计根节点数量
    int number() {
        unordered_set<int> roots;  // 自动去重
        // 遍历所有有效节点（1~n，节点0未使用）
        for (int i = 1; i < parent.size(); ++i) {
            roots.insert(find(i));  // 插入每个节点的根节点
        }
        return roots.size();  // 集合大小 = 集合数量
    }
};


//
class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;
    
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int findset(int x) {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    
    bool connected(int x, int y) {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};