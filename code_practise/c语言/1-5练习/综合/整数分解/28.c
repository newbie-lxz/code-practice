#include<stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int i;

    do{
        i=n%10;
        n /= 10;
        printf("%d ", i);
    }while(n>0);
    
    return 0;
}