#include<stdio.h>
int main()
{
    int a,b;
    scanf("%d",&a);
    int sum=0;
    for(b=0;a>0;a/=10){
        b=a%10;
        sum+=b;
    }
    printf("sum=%d",sum);
    return 0;
}