#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);

    int i = 1;
    double sum = 0.0;
    for(i=1; i<=n; i++){
        sum += 1.0/i; 
    }
    printf("sum = %lf", sum);
    return 0;
}