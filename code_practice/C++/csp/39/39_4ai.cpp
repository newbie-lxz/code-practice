#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
    题目：
    一棵 n 个节点的树。

    节点权值 a[1...n] 是 0 ~ n-1 的一个排列。

    每次询问 x, y：
    求 x 到 y 简单路径上所有节点权值集合的 mex。

    做法：
    1. 倍增 LCA
    2. 每个节点建立一棵“根 -> 当前节点”的主席树
    3. 查询路径时使用：

       root[x] + root[y]
       - root[lca]
       - root[parent[lca]]

    4. 主席树上寻找第一个没有出现的权值。
*/


// =======================
// 主席树节点
// =======================

struct Node
{
    int left;       // 左儿子编号
    int right;      // 右儿子编号
    int sum;        // 当前权值区间出现的节点数量

    Node() : left(0), right(0), sum(0) {}
};


// =======================
// 全局变量
// =======================

int n, m;

vector<int> a;

// 邻接表
vector<vector<int>> graph;

// root[u]：
// 从整棵树根节点 1 到 u 路径对应的主席树版本
vector<int> rootVersion;

// parent[u]
vector<int> parentNode;

// depth[u]
vector<int> depthNode;

// up[j][u]
// u 向上跳 2^j 步到达的节点
vector<vector<int>> up;

int LOG;


// 主席树节点数组
vector<Node> segTree;

// 当前已经用了多少主席树节点
int tot = 0;


// =======================
// 主席树修改
// =======================

/*
    pre：
        上一个版本的线段树根节点。

    [l,r]：
        当前权值区间。

    pos：
        当前要加入的权值。

    返回：
        新版本线段树的根节点。
*/

int update(int pre, int l, int r, int pos)
{
    // 创建新节点
    int now = ++tot;

    // 复制旧版本
    segTree[now] = segTree[pre];

    // 当前区间多了一个数
    segTree[now].sum++;

    // 到达叶子
    if(l == r)
        return now;

    int mid = (l + r) >> 1;

    if(pos <= mid)
    {
        /*
            pos 在左半边。

            只有左儿子发生变化，
            所以创建新的左儿子版本。
        */

        segTree[now].left =
            update(
                segTree[pre].left,
                l,
                mid,
                pos
            );
    }
    else
    {
        /*
            pos 在右半边。
        */

        segTree[now].right =
            update(
                segTree[pre].right,
                mid + 1,
                r,
                pos
            );
    }

    return now;
}


// =======================
// LCA
// =======================

int LCA(int u, int v)
{
    // 保证 u 更深
    if(depthNode[u] < depthNode[v])
        swap(u, v);

    /*
        第一步：

        把 u 向上跳，
        直到 u 和 v 深度一样。
    */

    int diff = depthNode[u] - depthNode[v];

    for(int j = 0; j < LOG; j++)
    {
        if(diff & (1 << j))
            u = up[j][u];
    }

    // 如果已经相等
    if(u == v)
        return u;

    /*
        第二步：

        u 和 v 一起往上跳。

        从大步开始。
    */

    for(int j = LOG - 1; j >= 0; j--)
    {
        if(up[j][u] != up[j][v])
        {
            u = up[j][u];
            v = up[j][v];
        }
    }

    /*
        此时：

        u 和 v 不相同，

        但是它们的父亲相同。

        所以父亲就是 LCA。
    */

    return up[0][u];
}


// =======================
// 求 mex
// =======================

/*
    rx = root[x]
    ry = root[y]
    rl = root[lca]
    rp = root[parent[lca]]

    当前需要表示：

    x -> y 路径上的权值。

    数量公式：

    root[x]
    + root[y]
    - root[lca]
    - root[parent[lca]]
*/

int queryMex(
    int rx,
    int ry,
    int rl,
    int rp,
    int l,
    int r
)
{
    /*
        当 l == r 时：

        已经找到唯一的一个权值。

        它就是最小缺失值。
    */

    if(l == r)
        return l;

    int mid = (l + r) >> 1;


    // 四个版本的左儿子
    int lx = segTree[rx].left;
    int ly = segTree[ry].left;
    int ll = segTree[rl].left;
    int lp = segTree[rp].left;


    /*
        求 x -> y 路径中：

        权值位于 [l, mid]

        的节点一共有几个。
    */

    int leftCount =
        segTree[lx].sum
        + segTree[ly].sum
        - segTree[ll].sum
        - segTree[lp].sum;


    /*
        [l,mid] 区间中

        理论上一共有多少个不同数字？
    */

    int leftSize = mid - l + 1;


    /*
        因为所有权值是排列，
        每个权值最多出现一次。

        如果：

            leftCount < leftSize

        说明左半边至少有一个权值没有出现。

        mex 是最小缺失值，
        所以一定在左边。
    */

    if(leftCount < leftSize)
    {
        return queryMex(
            lx,
            ly,
            ll,
            lp,
            l,
            mid
        );
    }


    /*
        否则说明：

        [l,mid]

        中所有数字全部出现。

        mex 只能在右半边。
    */

    return queryMex(
        segTree[rx].right,
        segTree[ry].right,
        segTree[rl].right,
        segTree[rp].right,
        mid + 1,
        r
    );
}


// =======================
// main
// =======================

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    // -----------------------
    // 输入 n,m
    // -----------------------

    cin >> n >> m;


    // -----------------------
    // 权值
    // -----------------------

    a.resize(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> a[i];


    // -----------------------
    // 建邻接表
    // -----------------------

    graph.resize(n + 1);

    for(int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }


    // -----------------------
    // 计算 LOG
    // -----------------------

    LOG = 1;

    while((1 << LOG) <= n)
        LOG++;


    up.assign(LOG, vector<int>(n + 1, 0));

    parentNode.assign(n + 1, 0);
    depthNode.assign(n + 1, 0);

    rootVersion.assign(n + 1, 0);


    /*
        每个节点加入主席树时：

        大约创建 log n 个节点。

        所以总共约：

        n * log n

        再稍微多留一点空间。
    */

    int maxSegNodes =
        (n + 5) * (LOG + 3);

    segTree.resize(maxSegNodes);


    // -----------------------
    // 从节点1开始遍历整棵树
    // -----------------------

    stack<int> st;

    st.push(1);

    parentNode[1] = 0;
    depthNode[1] = 0;


    /*
        根节点版本：

        空版本 root[0]

        加入 a[1]
    */

    rootVersion[1] =
        update(
            0,
            0,
            n,
            a[1]
        );


    while(!st.empty())
    {
        int u = st.top();
        st.pop();


        for(int v : graph[u])
        {
            // 不往父亲走
            if(v == parentNode[u])
                continue;


            // -------------------
            // 父节点
            // -------------------

            parentNode[v] = u;


            // -------------------
            // 深度
            // -------------------

            depthNode[v] =
                depthNode[u] + 1;


            // -------------------
            // LCA 倍增数组
            // -------------------

            up[0][v] = u;

            for(int j = 1; j < LOG; j++)
            {
                up[j][v] =
                    up[j - 1][
                        up[j - 1][v]
                    ];
            }


            // -------------------
            // 主席树
            // -------------------

            /*
                root[v]

                = root[u]

                再加入当前节点权值 a[v]
            */

            rootVersion[v] =
                update(
                    rootVersion[u],
                    0,
                    n,
                    a[v]
                );


            st.push(v);
        }
    }


    // -----------------------
    // 处理 m 次询问
    // -----------------------

    while(m--)
    {
        int x, y;

        cin >> x >> y;


        // 最近公共祖先
        int l = LCA(x, y);


        /*
            l 的父节点。

            如果 l == 1：

            parent[1] == 0。

            rootVersion[0] 是空线段树，
            所以没有问题。
        */

        int p = parentNode[l];


        int ans =
            queryMex(
                rootVersion[x],
                rootVersion[y],
                rootVersion[l],
                rootVersion[p],
                0,
                n
            );


        cout << ans << '\n';
    }


    return 0;
}