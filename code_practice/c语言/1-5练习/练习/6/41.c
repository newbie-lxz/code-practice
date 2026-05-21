#include<stdio.h>
int main()
{
    int n,t;
    double a=2,b=1;
    int cnt;
    double sum=0;
    //scanf("%d", &n);
    n=20;
    for(cnt=0;cnt<n;cnt++){
        double f=a/b;
        t=b;
        b=a;
        a+=t;
        sum+=f;
    }
    printf("sum=%.2f", sum);
    return 0;
}