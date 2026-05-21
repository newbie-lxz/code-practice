#include<stdio.h>
int main()
{
    int n = 1,x = 1;
    while( ++n < 6){ x = x * n; printf("%0d %0d\n", n, x); }
    return 0;
}