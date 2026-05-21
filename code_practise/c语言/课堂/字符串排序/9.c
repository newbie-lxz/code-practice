#include <stdio.h>

int main(void)
{
    struct st
    {
        int x, *y;
    } *p, *q;
    int s[] = {10, 20, 30, 40};
    struct st a[] = {1, &s[0], 2, &s[1], 4, &s[2], 8, &s[3]};
    p = a;
    printf("%d\n", ++(*(++p)->y));
    q = p++;
    printf("%d\n", ++(*(++q)->y));
    printf("%d\n", (++p)->x);
    printf("%d\n", ++q->x);
    printf("%5d\n", (*(--p)).y - (*(++q)).y);
}