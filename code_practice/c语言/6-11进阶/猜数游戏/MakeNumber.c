#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"MakeNumber.h"
/*
函数功能：随机生成一个随机数
函数参数：无
函数返回值：返回计算机生成的随机数
*/

int MakeNumber(void)
{
    int number;
    number = (rand()%(MAX_NUMBER - MIN_NUMBER + 1)) + MIN_NUMBER;
    assert(number >= MIN_NUMBER && number <= MAX_NUMBER);
    return number;
}