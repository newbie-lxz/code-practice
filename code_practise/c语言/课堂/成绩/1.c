#include<stdio.h>
int main()
{
    printf("请输入您的成绩");
    int grade;
    scanf("%d",&grade);
    if(grade>=95){
        grade=100;
    }
    grade/=10;
    switch(grade) {
        case 10:
            printf("A\n");
            break;
        case 9:
        case 8:
            printf("B\n");
            break;
        case 7:
        case 6:
            printf("C\n");
            break;
        default :
            printf("不及格\n");
            break;
    }
    return 0;
}