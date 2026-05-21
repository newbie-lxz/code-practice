#include<stdio.h>
int main()
{
    int n;
    scanf("%d", &n);

    int i;
    int isPrime = 1; 
    for(i=2; i<n; i++){
        if(n % i == 0){
            isPrime = 0;
            break;
        }
    }
    if (isPrime == 1){
        printf("%d是素数\n",n);
    }else {
        printf("%d不是素数\n", n);
    }
    return 0;
}