#include <stdio.h>

// 函数声明
void josephus(int n, int m, int k);

int main() {
    int n, m, k;
    printf("请输入总人数 n、报数 m 和起始位置 k: ");
    scanf("%d %d %d", &n, &m, &k);
    josephus(n, m, k);
    return 0;
}

// 约瑟夫问题的数学解法（从第 k 个人开始，并输出每一次出列的编号）
void josephus(int n, int m, int k) {
    int people[n];
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }

    int current = k - 1;
    while (n > 1) {
        int count = m % n;
        if (count == 0) {
            count = n;
        }
        current = (current + count - 1) % n;
        printf("出列的是：%d\n", people[current]);
        for (int i = current; i < n - 1; i++) {
            people[i] = people[i + 1];
        }
        n--;
    }
    printf("最后剩下的是：%d\n", people[0]);
}