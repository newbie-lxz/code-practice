#include<stdio.h>
#include<stdlib.h>
int gcd(int a,int b){
    while(b!=0){
        int t=a%b;
        a=b;
        b=t;
    }
    return a;
}
int main()
{
    int divisor,dividend;
    scanf("%d/%d", &dividend,&divisor);
    int x=gcd(divisor,dividend);
    printf("%d/%d\n",dividend/x,divisor/x);
    system("pause");
    return 0;
}