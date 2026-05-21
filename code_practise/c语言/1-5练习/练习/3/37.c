#include<stdio.h>
int main()
{
    int n,c;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            c=i*j;
            printf("%d*%d=%d  ",i,j,c);
        }
        printf("\n");
    }
    return 0;
}