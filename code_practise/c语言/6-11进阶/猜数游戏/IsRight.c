#include<stdio.h>
#include"IsRight.h"
/*
函数功能：判断guess和number大小，分别给出相应的提示
函数参数：number是被猜的数，guess是猜的数
函数返回值：猜对为1；否则为0
*/
int IsRight(int number, const int guess)
{
    if(guess < number){
        printf("Wrong! Too small!\n");
        return 0;
    }else if(guess > number){
        printf("Wrong! Too big!\n");
        return 0;
    }else{
        return 1;
    }
}