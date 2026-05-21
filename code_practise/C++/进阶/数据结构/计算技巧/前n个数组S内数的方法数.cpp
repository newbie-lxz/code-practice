#include <iostream>
#include <vector>
using namespace std;

vector<int> dp;
int S;

void init(int n)
{
    S = n * (n + 1) / 2;
    dp.resize(S/2+1);
    dp[0] = 1; 
    for (int i = 1; i <= n; ++i) 
    {
        for (int j = S/2; j >= i; --j) 
        {
            dp[j] += dp[j - i];
            if(dp[j]>=100000007)
            dp[j] -= 100000007;
        }
    }
}

// int main()
// {
//     long long n,s,a,b,ans = 0,l,r;
//     cin>>n>>s>>a>>b;
//     long long num = a+b;
//     s += (n-1)*n/2*b;
//     r = s/n;
//     l = (s-(n-1)*n/2*num)/n;

//     init(n-1);
//     for(;l<=r; l++)
//     {
//         long long temp = s - n*l;
//         if(temp%num==0)
//         {
//             int sum = temp/num;
//             if(sum>S/2)
//             {
//                 sum = S-sum;
//             }
//             ans+=dp[sum];
//             ans %= 100000007;
//         }
//     }
//     cout<<ans;
//     return 0;
// }