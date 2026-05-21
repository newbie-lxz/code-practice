#include <stdio.h>
#include <stdlib.h>
int i = 1;
void func()
{
static int a = 1;
int b = 1;
int c = 1;
b = a++;
i = b;
printf("func: i=%d a=%d b=%d c=%d\n", i, a, b, c);
}
int main()
{
int a;
register int b = 1;
int c = 0;
int d[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int *p1 = d;
int (*p2)[3] = d;
printf("main: i=%d a=%d b=%d c=%d \n", i, a, b, c);
c = (++p1)[i];
func();
printf("main: i=%d a=%d b=%d c=%d\n", i, a, b, c);
c = *(p2 + a)[i];
func();
printf("main: i=%d a=%d b=%d c=%d\n", i, a, b, c);
return 0;
}