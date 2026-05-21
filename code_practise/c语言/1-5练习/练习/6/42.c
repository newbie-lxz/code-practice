#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n;
    double dividend/*分子*/,divisor/*分母*/;
    double sum=0.0;
    int i;
    double t;
    scanf("%d",&n);
    dividend=2;
    divisor=1;
    for(i=1;i<=n;i++){
        sum+=dividend/divisor;
        t=dividend;
        dividend=dividend+divisor;
        divisor = t;
    }
    printf("%.2f\n",sum);
    system("PAUSE");
    return 0;
}