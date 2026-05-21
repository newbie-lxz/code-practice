#include<stdio.h>
int main()
{
    double y=3.14;
    int x=5;
    int *p = &x;
    printf("p的值为:%p\n",p);
    printf("p + 1的值为:%p\n", p + 1);
    printf("(double*)(p + 1)的值为:%p\n", (double*)(p + 1));
    printf("(double*)p的值为:%p\n",(double*)p);
    printf("(double*)p + 1的值为:%p\n", (double*)p + 1);

    *(p+1)=10;
    *(p+2)=-5;

    printf("y的值为:%lf\n",y);
    printf("*((double*)(p+1))的值为:%lf\n",*((double*)(p+1)));
    printf("*((double*)p+1)的值为:%lf\n",*((double*)p+1));

    return 0;
}