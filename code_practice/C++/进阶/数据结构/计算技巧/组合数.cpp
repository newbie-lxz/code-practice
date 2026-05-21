#include <iostream>
using namespace std;

const int MOD = 100000007;
long long fz[1001]; // 分子：n*(n-1)*...*(n-k+1) mod MOD
long long fm[1001]; // 分母：k! mod MOD
long long inv_fm[1001]; // 分母的逆元：(k!)^{-1} mod MOD

// 快速幂：计算 (base^exp) % mod（用于求逆元）
long long quick_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod; // 先取模，避免base溢出
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// 初始化：预处理分子、分母、分母的逆元
void init(int n) {
    // 边界条件：C(n,0)=1，对应分子/分母都是1
    fz[0] = 1;
    fm[0] = 1;
    inv_fm[0] = 1; // 1的逆元是1
    
    // 预处理分子：fz[k] = n*(n-1)*...*(n-k+1) mod MOD
    fz[1] = n % MOD; // 先取模，避免n>MOD时溢出
    // 预处理分母：fm[k] = k! mod MOD
    fm[1] = 1;
    inv_fm[1] = 1; // 1!的逆元是1
    
    for (int i = 2; i <= n; ++i) {
        // 分子：前一项 * (n-i+1)，每次取模避免溢出
        fz[i] = (fz[i-1] * ((n - i + 1) % MOD)) % MOD;
        // 分母：前一项 * i，每次取模
        fm[i] = (fm[i-1] * i) % MOD;
        // 预处理分母的逆元：(i!)^{-1} = (i-1)!^{-1} * i^{-1} mod MOD
        inv_fm[i] = (inv_fm[i-1] * quick_pow(i, MOD-2, MOD)) % MOD;
    }
}

// 计算组合数 C(n,k) mod MOD
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    // C(n,k) = (分子) * (分母的逆元) mod MOD
    return (fz[k] * inv_fm[k]) % MOD;
}





/*
#include <iostream>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;  // 必须是质数！常用 1e9+7, 998244353
const int MAX = 500001;  // n 最大 = 1e6，想更大直接改这个数！

ll fact[MAX];   // 阶乘数组: fact[i] = i! % MOD
ll inv_fact[MAX]; // 逆元阶乘: inv_fact[i] = 1/(i!) % MOD

// 快速幂：求 a^b % mod
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 预处理：O(n)
void init() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    // 费马小定理求逆元
    inv_fact[MAX-1] = qpow(fact[MAX-1], MOD-2);
    for (int i = MAX-2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
}

// 查询组合数：O(1)
ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// 使用示例
int main() {
    init();
    cout << C(1000000, 500000) << endl; // 百万级别秒算！
    return 0;
}
*/
