#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    srand(time(0));
    int number = rand()%100+1;
    int count = 0;
    int a = 0;
    printf ("我已经想好了一个1到100的数字。");
    do{
        printf("猜猜这个数字是多少：");
        scanf("%d",&a);
        count ++;
        if(a>number){
            printf("你猜的偏大。");
        }else if(a<number){
            printf("你猜的偏小。");
        }    
    }while(a!=number);
    printf("恭喜你，猜对了！你用了%d次就猜到了正确数字。\n", count);

    return 0;
}