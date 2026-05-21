#include<stdio.h>
#include"IsRight.h"
#include"IsValidNum.h"
/*
函数功能：用户猜数字
函数参数:number是计算机随机生成的数字
函数返回值：无
*/

void GuessNumber(int number)
{
    int guess;
    int count = 0;
    int right = 0;
    int ret;
    do{
        printf("Try%d:",count + 1);
        ret = scanf("%d",&guess);

        while(ret!=1 || !IsValidNum(guess))
        {
            printf("Input error! \n");
            while(getchar() != '\n');
            printf("Try%d:", &count + 1);
            ret = scanf("%d",&guess);
        }
        count++;
        right = IsRight(number,guess);
    }while(!right && count <MAX_TIMES);
    if(right){
        printf("Congratulation! You're so cool!\n");
    }else{
        printf("Mission failed after%d attempts.\n",MAX_TIMES);
    }
}