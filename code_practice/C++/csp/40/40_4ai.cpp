#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op, n;
    cin >> op >> n;

    /*
        spf[x]：
        x 的最小质因子
    */
    vector<int> spf(n + 1);
    vector<int> primes;

    /*
        线性筛最小质因子
    */
    for(int i = 2; i <= n; i++)
    {
        if(spf[i] == 0)
        {
            spf[i] = i;
            primes.push_back(i);
        }

        for(int p : primes)
        {
            ll v = 1LL * i * p;

            if(v > n || p > spf[i])
                break;

            spf[v] = p;
        }
    }


    /*
        inv[x]：
        x 在 MOD 意义下的逆元

        因为 n < MOD，所以1~n都有逆元
    */
    vector<int> inv(n + 1);

    inv[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        inv[i] =
            MOD -
            1LL * (MOD / i) * inv[MOD % i] % MOD;
    }


    /*
        pp[x]：
        x 中最小质因子的完整幂次部分

        例如：

        x = 72 = 2^3 * 3^2

        pp[72] = 2^3 = 8
    */
    vector<int> pp(n + 1);


    /*
        五个积性函数：

        F：所有合法(a,b)的 ab 之和

        H：a=1 或 b=1 时使用

        J：a=b 时使用

        C：ab=1 时使用

        K：a^2 b=1 / ab^2=1 时使用
    */
    vector<int> F(n + 1);
    vector<int> H(n + 1);
    vector<int> J(n + 1);
    vector<int> C(n + 1);
    vector<int> K(n + 1);


    pp[1] = 1;

    F[1] = 1;
    H[1] = 1;
    J[1] = 1;
    C[1] = 1;
    K[1] = 1;


    /*
        x = 1：

        普通C形阵只有：

        1 1 1
        1
        1 1 1

        价值为1。

        但是它显然不是完美C形阵。
    */
    ll ans;

    if(op == 0)
        ans = 1;
    else
        ans = 0;


    for(int x = 2; x <= n; x++)
    {
        int p = spf[x];

        int y = x / p;

        /*
            求 x 中 p 的完整幂次。

            例如：

            x = 12
            p = 2

            pp[12] = 4
        */
        if(y % p == 0)
        {
            pp[x] = pp[y] * p;
        }
        else
        {
            pp[x] = p;
        }


        /*
            去掉 p^k 之后剩下的部分
        */
        int rest = x / pp[x];


        /*
            如果 rest == 1：

            说明 x 本身就是质数幂：

            x = p^k

            直接计算：
            F(p^k)
            H(p^k)
            J(p^k)
            C(p^k)
            K(p^k)
        */
        if(rest == 1)
        {
            int k = 0;
            int temp = x;

            while(temp % p == 0)
            {
                temp /= p;
                k++;
            }


            /*
                p 的正指数和负指数。

                pw[i]  = p^i
                ipw[i] = p^(-i)
            */
            ll pw[64];
            ll ipw[64];

            pw[0] = 1;
            ipw[0] = 1;

            for(int i = 1; i <= 2 * k; i++)
            {
                pw[i] =
                    pw[i - 1] * p % MOD;

                ipw[i] =
                    ipw[i - 1] * inv[p] % MOD;
            }


            /*
                返回 p^e。

                e可以为负数。
            */
            auto power = [&](int e) -> ll
            {
                if(e >= 0)
                    return pw[e];

                return ipw[-e];
            };


            // =============================
            // 计算 F(p^k)
            // =============================

            ll sumF = 0;

            for(int alpha = -k;
                alpha <= k;
                alpha++)
            {
                for(int beta = -k;
                    beta <= k;
                    beta++)
                {
                    /*
                        abx必须是整数：

                        alpha + beta + k >= 0
                    */
                    if(alpha + beta >= -k)
                    {
                        sumF += power(alpha + beta);

                        if(sumF >= 1LL * MOD * MOD)
                            sumF %= MOD;
                    }
                }
            }

            F[x] = sumF % MOD;


            // =============================
            // 计算 H(p^k)
            // =============================

            ll sumH = 0;

            for(int alpha = -k;
                alpha <= k;
                alpha++)
            {
                sumH += power(alpha);

                if(sumH >= MOD)
                    sumH -= MOD;
            }

            H[x] = sumH;


            // =============================
            // 计算 J(p^k)
            //
            // a = b
            // =============================

            ll sumJ = 0;

            /*
                ceil(-k/2)

                k=1 -> 0
                k=2 -> -1
                k=3 -> -1
                k=4 -> -2
            */
            int low = -(k / 2);

            for(int alpha = low;
                alpha <= k;
                alpha++)
            {
                sumJ += power(2 * alpha);
                sumJ %= MOD;
            }

            J[x] = sumJ;


            // =============================
            // 计算 C(p^k)
            //
            // ab = 1
            // =============================

            C[x] = 2 * k + 1;


            // =============================
            // 计算 K(p^k)
            //
            // a^2 b = 1
            // =============================

            ll sumK = 0;

            int high = k / 2;

            for(int alpha = low;
                alpha <= high;
                alpha++)
            {
                sumK += power(-alpha);

                if(sumK >= MOD)
                    sumK -= MOD;
            }

            K[x] = sumK;
        }

        /*
            如果：

            x = p^k * rest

            并且：

            gcd(p^k, rest) = 1

            因为这些函数都是积性函数：

            F(x)
            =
            F(p^k) * F(rest)
        */
        else
        {
            int q = pp[x];

            F[x] =
                1LL * F[q] * F[rest] % MOD;

            H[x] =
                1LL * H[q] * H[rest] % MOD;

            J[x] =
                1LL * J[q] * J[rest] % MOD;

            C[x] =
                1LL * C[q] * C[rest] % MOD;

            K[x] =
                1LL * K[q] * K[rest] % MOD;
        }


        ll cur;


        if(op == 0)
        {
            /*
                普通 C 形阵：

                当前 x 的 ab 总和就是 F[x]
            */
            cur = F[x];
        }
        else
        {
            /*
                完美 C 形阵：

                F
                - 2H
                - J
                - C
                - 2K
                + 5
            */

            cur = F[x];

            cur -= 2LL * H[x];
            cur %= MOD;

            cur -= J[x];
            cur %= MOD;

            cur -= C[x];
            cur %= MOD;

            cur -= 2LL * K[x];
            cur %= MOD;

            cur += 5;
            cur %= MOD;

            if(cur < 0)
                cur += MOD;
        }


        /*
            实际价值：

            D = ab * x

            所以乘一个 x
        */
        ans += 1LL * x * cur % MOD;
        ans %= MOD;
    }


    cout << ans << '\n';

    return 0;
}