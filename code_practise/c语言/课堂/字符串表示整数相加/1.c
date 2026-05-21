#include <stdio.h>
#include <string.h>

int main() {
    char str1[1000], str2[1000];
    scanf("%s", str1);
    scanf("%s", str2);
    //计算字符串长度
    int length1 = strlen(str1);
    int length2 = strlen(str2);
    int a = 0;
    char result[1001];
    int b = 0;
    int i = length1 - 1;
    int j = length2 - 1;
    while (i >= 0 || j >= 0 || a > 0) {
        int digit1 = (i >= 0)? str1[i] - '0' : 0;//-'0'表示把字符转化为数字
        int digit2 = (j >= 0)? str2[j] - '0' : 0;
        int sum = digit1 + digit2 + a;
        a = sum / 10;
        result[b++] = (sum % 10) + '0';
        i--;
        j--;
    }
    for (int k = b - 1; k >= 0; k--) {
        printf("%c", result[k]);
    }
    printf("\n");
    return 0;
}