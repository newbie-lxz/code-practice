#include<stdio.h>
int main()
{
    int x=5;
    double y=3.14;
    int *p = &x;
    printf("p的值为:%p\n",p);
    printf("p + 1的值为:%p\n", p + 1);
    printf("(double*)(p + 1)的值为:%p\n", (double*)(p + 1));
    printf("(double*)p的值为:%p\n",(double*)p);
    printf("(double*)p + 1的值为:%p\n", (double*)p + 1);


    return 0;
}