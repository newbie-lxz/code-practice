#include <stdio.h>

// 函数声明
int josephus(int n, int m, int k);

int main() {
    int n, m, k;
    printf("请输入总人数 n、报数 m 和起始位置 k: ");
    scanf("%d %d %d", &n, &m, &k);
    int result = josephus(n, m, k);
    printf("最后剩下的人的编号是: %d\n", result);
    return 0;
}

// 约瑟夫问题的数学解法（从第 k 个人开始）
int josephus(int n, int m, int k) {
    if (n == 1)
        return 1;
    else {
        int prevSurvivor = josephus(n - 1, m, k);
        int newPosition = (prevSurvivor + m - 1) % n + 1;
        // 如果新位置在起始位置之前，需要调整
        if (newPosition < k) {
            newPosition += n - k + 1;
        } else {
            newPosition -= k - 1;
        }
        return newPosition;
    }
}