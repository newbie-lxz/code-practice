#include<stdio.h>
int main()
{
    int n;
    for(n=32;n<=100;n++){
        int a=n*n;
        int b=(a/100)%11;
        int c=(a%100)%11;
        if(b==0&&c==0&&a%1111!=0){
            printf("%d\n",a);
        }
    }
    return 0;
} 