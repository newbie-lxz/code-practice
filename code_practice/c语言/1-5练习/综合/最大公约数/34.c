#include<stdio.h>
int main()
{
    //辗转相除
    int a,b,c;
    scanf("%d %d", &a, &b);
    while(b!=0){
        c=a%b;
        a=b;
        b=c;
    }
    printf("最大公约数是%d\n", a);
}