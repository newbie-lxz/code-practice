#include <math.h>
#include <stdio.h>

int minSquares(int n) {
    int count = 0;
    int count2 =0;
    int n2=n;
    while (n > 0) {
        int square = (int)sqrt(n);
        n -= square * square;
        count++;
    }
    int square2 = (int)sqrt(n2)-1;
    while(n2>0){
        n2 -= square2 * square2;
        square2 = (int)sqrt(n2);
        count2++;
    }
    if(count>=count2){
        return count2;
    }else{
        return count;
    } 
}

int main() {
    int n;
    printf("请输入一个正整数：");
    scanf("%d", &n);
    printf("最小数量的完美平方数为：%d\n", minSquares(n));
    return 0;
}  