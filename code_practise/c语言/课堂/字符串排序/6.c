#include <stdio.h>

int main()
{
    short int *p1;
    long int *p3;
    short int score[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    p1 = score;
    p3 = (long int*)score;
    printf("%p, %p\n", p1 + 1, p3 + 1);
    printf("%d, %d\n", *p1, *p3);
    return 0;
}