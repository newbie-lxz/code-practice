#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;

ll qsm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll inv(ll q){return qsm(q,mod-2);}  // 费马小定理求逆元  求q的逆元，前提mod为质数



const int MAX = 1e5 + 9;
ll fac[MAX], inv_fac[MAX];

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAX; i++)
        fac[i] = fac[i-1] * i % mod;

    inv_fac[MAX-1] = qsm(fac[MAX-1], mod-2);
    for (int i = MAX-2; i >= 0; i--)
        inv_fac[i] = inv_fac[i+1] * (i+1) % mod;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fac[n] * inv_fac[k] % mod * inv_fac[n-k] % mod;
}
//(C(n,k))组合数


typedef long long ll;

// exgcd 模板
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 求 a 在模 m 下的逆元（mod 可以不是质数！）
ll inv(ll a, ll m) {
    ll x, y;
    ll d = exgcd(a, m, x, y);
    if (d != 1) return -1; // 不互质，无逆元！
    return (x % m + m) % m; // 保证是正数
}//(a,m)=1;1