#include<stdio.h>
int main()
{
    int x;
    int n;
     
    printf("请输入数字：");
    scanf("%d", &x);

    do{
        x/=10;
        n++;
    } while(x>0);

    printf("%d", n);

    return 0;
}