#include<stdio.h>
int main()
{
    int n;
    printf("请输入数字：");
    scanf("%d",&n);

    int ret;
    ret = 1;

    while(n>0){
        ret *= n;
        --n; 
    };
    printf("阶乘为：%d", ret);

    return  0;
}