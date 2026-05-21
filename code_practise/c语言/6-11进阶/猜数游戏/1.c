#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "guess.h"

int main(void)
{
    int number;
    char reply;
    srand(time(NULL));
    do{
        number = MakeNumber();
        GuessNumber(number);
        printf("Do you want to continue(Y/N or y/n)?");
        scanf(" %c",&reply);                            //%c前面有空格
    }while(reply=='Y'||reply=='y');
    return 0;
}