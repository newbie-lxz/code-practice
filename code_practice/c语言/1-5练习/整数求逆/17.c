#include<stdio.h>
int main()
{
    int x;
    scanf("%d",&x);

    int digit;
    digit = 0;
    int y;
    y = 0;
    
    do{
    y = y*10;
    digit = x%10;
    x /= 10;
    y = y+digit;}while(x>0);

    printf("%d",y);
    return 0;
}