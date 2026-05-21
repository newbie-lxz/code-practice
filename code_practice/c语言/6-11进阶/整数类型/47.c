#include<stdio.h>
int main ()
{
    printf("sizeof(char)=%ld\n", sizeof(char));//1
    printf("sizeof(short)=%ld\n", sizeof(short));//2
    printf("sizeof(int)=%ld\n", sizeof(int));//4
    printf("sizeof(long)=%ld\n", sizeof(long));//4
    printf("sizeof(long long)=%ld\n", sizeof(long long));//8
    return 0;
}