#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MOD 998244353

int gcd(int a, int b)
{
    while(b)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

long long sum_lr(long long L, long long R)
{
    long long x = L + R;
    long long y = R - L + 1;

    if(x % 2 == 0)
        x /= 2;
    else
        y /= 2;

    return (x % MOD) * (y % MOD) % MOD;
}


int main()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    vector<pair<int,int>> g;

    long long ans = 0;

    for(int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }

    for(int r = 1; r <= n; r++)
    {
        for(int i = 0; i < (int)g.size(); i++)
        {
            g[i].second = gcd(g[i].second, v[r]);
        }
        vector<pair<int,int>> ng;

        for(int i = 0; i < (int)g.size(); i++)
        {
            if(ng.empty() || ng.back().second != g[i].second)
            {
                ng.push_back(g[i]);
            }
        }

        g.swap(ng);

        if(g.empty() || g.back().second != v[r])
        {
            g.push_back({r, v[r]});
        }

        for(int i = 0; i < (int)g.size(); i++)
        {
            int L = g[i].first;
            int R;
            if(i + 1 < (int)g.size())
            {
                R = g[i + 1].first - 1;
            }
            else
            {
                R = r;
            }

            long long sumL = sum_lr(L, R);
            long long contribution = (1LL * r * g[i].second) % MOD;

            contribution = contribution * sumL % MOD;

            ans += contribution;
            ans %= MOD;
        }
    }

    cout << ans;

    return 0;
}