#include<stdio.h>
int main()
{
    int x;
    int y;
    int n;
    int i;

    scanf("%d", &x);
    scanf("%d", &y);
    
    for(i=1; i<=x; i++){
        if(x%i==0){
            if(y%i==0){
                n=i;
            }
        }
    }
    printf("最大公约数为：%d", n);
    return 0;
}