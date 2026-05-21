#include <stdio.h>
int main()
{
    int hour1, mintue1;
    int hour2, mintue2;

    scanf("%d %d",&hour1, &mintue1);
    scanf("%d %d",&hour2, &mintue2);

    int ih = hour2 - hour1;
    int im = mintue2 - mintue1;
    if (im<0){
        im = im + 60;
        ih--;
    }

    printf ("时间差是%d小时%d分钟。\n",ih ,im);

    return 0;
}