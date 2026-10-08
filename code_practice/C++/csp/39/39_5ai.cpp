#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    一个状态值用两个量表示：

    first  : 调整后的费用
    second : -完成题数

    为什么存负数？
    因为 priority_queue<pair<...>, ..., greater<...>>
    会按照 pair 从小到大比较。

    当费用一样时：
    -完成题数越小
    => 完成题数越大
    => 优先选择完成更多题的方案
*/
using P = pair<ll, ll>;

int n;
ll m;

vector<ll> a, b;


/*
    check(lambda2)

    lambda2 = 2 * lambda

    lambda 可以理解成：

        “每完成一道题，给你 lambda 点奖励”

    原问题本来是：

        最小化 cost

    加入奖励以后：

        最小化 cost - lambda * 完成题数

    返回：
        {在这个 lambda 下完成多少题, 实际花费多少}
*/
pair<ll, ll> check(ll lambda2)
{
    /*
        小根堆。

        堆里维护 DP 函数的“斜率”。

        你现在可以先把它理解成：
        用堆压缩掉原来需要枚举的“库存题数”这一维。
    */
    priority_queue<P, vector<P>, greater<P>> q;

    /*
        f0 表示：

        当前处理完这些天，
        最后“待验题数量 = 0”时的最优值。

        f0.first  = 调整费用的 2 倍
        f0.second = -完成题数
    */
    P f0 = {0, 0};

    for(int i = 1; i <= n; i++)
    {
        /*
            第 i 天四种情况：

            1. 两人都休息
            2. 只有 C 造题
            3. 只有 F 验题
            4. C 上午造，F 下午验

            引入 lambda 奖励以后，
            “完成一道题”都会减去 lambda。
        */

        // 今天什么都不干
        P doNothing = {0, 0};

        /*
            今天 C、F 都工作：

            实际费用 = a[i] + b[i]
            完成题数 +1

            因为我们全部扩大2倍：
            调整费用 =
            2*(a[i]+b[i]) - lambda2

            second = -1
            表示完成题数增加1
        */
        P doBoth = {
            2LL * (a[i] + b[i]) - lambda2,
            -1
        };

        /*
            center：
            在“今天都不干”和“今天直接完成一题”之间
            选择更优的。
        */
        P center = min(doNothing, doBoth);


        /*
            onlyCheck：
            F 今天验掉一道之前已经造好的题。

            费用 b[i]
            完成题数 +1
        */
        P onlyCheck = {
            2LL * b[i] - lambda2,
            -1
        };


        /*
            onlyMake：
            C 今天只造一道题。

            花费 a[i]
            但还没验，因此完成题数不增加。
        */
        P onlyMake = {
            2LL * a[i],
            0
        };


        /*
            下面两个值是这一轮 DP 更新后
            新产生的两个“斜率”。

            pair 的减法需要自己写。
        */
        P lower = {
            center.first - onlyCheck.first,
            center.second - onlyCheck.second
        };

        P upper = {
            onlyMake.first - center.first,
            onlyMake.second - center.second
        };


        /*
            先把今天最基础的贡献加进来。
        */
        f0.first += center.first;
        f0.second += center.second;


        /*
            如果之前最小的斜率比 lower 还小，
            说明最优 DP 的凸性需要调整。

            就把最小的旧斜率替换成 lower。
        */
        if(!q.empty() && q.top() < lower)
        {
            P old = q.top();
            q.pop();

            f0.first += old.first - lower.first;
            f0.second += old.second - lower.second;

            q.push(lower);
        }


        /*
            新的右侧斜率加入堆。
        */
        q.push(upper);
    }


    /*
        f0.second 存的是 -完成题数
    */
    ll cnt = -f0.second;


    /*
        f0.first 现在是：

        2*真实费用 - lambda2*cnt

        所以：

        2*真实费用
        = f0.first + lambda2*cnt
    */
    ll realCost2 = f0.first + lambda2 * cnt;

    ll realCost = realCost2 / 2;

    return {cnt, realCost};
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    a.resize(n + 1);
    b.resize(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> a[i];

    for(int i = 1; i <= n; i++)
        cin >> b[i];


    /*
        接下来二分 lambda。

        lambda 越大：

        “完成一道题”的奖励越高，

        所以最优方案倾向于完成更多题。

        因此完成题数具有单调性。
    */

    ll left = 0;
    ll right = 1;


    /*
        先找到一个足够大的 lambda，
        使最优方案愿意完成 n 道题。
    */
    while(check(right).first < n)
    {
        right *= 2;
    }


    /*
        二分找到一个临界 lambda。

        我们希望：
        check(lambda) 对应方案的真实花费 <= m。
    */
    while(left < right)
    {
        ll mid = (left + right + 1) / 2;

        auto [cnt, cost] = check(mid);

        if(cost <= m)
            left = mid;
        else
            right = mid - 1;
    }


    /*
        left 是预算内的临界奖励。

        再检查 left 和 left+1 两边。
    */
    auto L = check(left);

    ll cnt1 = L.first;
    ll cost1 = L.second;


    // 已经可以完成全部 n 道
    if(cnt1 == n)
    {
        cout << n << '\n';
        return 0;
    }


    auto R = check(left + 1);

    ll cnt2 = R.first;
    ll cost2 = R.second;


    // left+1 也没有超过预算
    if(cost2 <= m)
    {
        cout << cnt2 << '\n';
        return 0;
    }


    // 两边完成题数相同
    if(cnt1 == cnt2)
    {
        cout << cnt1 << '\n';
        return 0;
    }


    /*
        可能出现一次跳很多题，例如：

        left：
            完成 5 题
            花费 100

        left+1：
            完成 9 题
            花费 140

        相当于增加：

            4题花40

        每多完成一道题的边际费用：

            40 / 4 = 10
    */
    ll marginalCost =
        (cost2 - cost1) / (cnt2 - cnt1);


    /*
        现在还剩：

            m - cost1

        看还能买几个这样的“边际题目”。
    */
    ll extra =
        (m - cost1) / marginalCost;

    extra = min(extra, cnt2 - cnt1);


    cout << cnt1 + extra << '\n';

    return 0;
}