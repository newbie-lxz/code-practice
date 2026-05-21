#include <stdio.h>
#include<math.h> 
#include <limits.h>
int numSquares(int n) {
    int dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            dp[i] = fmin(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}

int main() {
    int n;
    printf("请输入一个正整数: ");
    scanf("%d", &n);
    int result = numSquares(n);
    printf("最小数量的完美平方数为: %d\n", result);
    return 0;
}