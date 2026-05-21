#include<stdio.h>
long long int num(int n)
{
    long long int sum=1;
    for(int i=1;i<n;i++){
        sum=(sum+1)*2;
    }
    return sum;
}
int main()
{   int m;
    printf("请输入天数:");
    scanf("%d",&m);
    printf("第一天有%lld个桃子",num(m));
    return 0;
}