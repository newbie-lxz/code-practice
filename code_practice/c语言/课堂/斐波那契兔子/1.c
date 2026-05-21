#include<stdio.h>
int main()
{
    int month,sum,sum1,SUM1;
    int i=2;
    sum=1;
    sum1=0;
    to:
    printf("请输入月份:\n");
    scanf("%d", &month);
    if(month<=2&&month>0){
        printf("1\n");
    }else if(month<=0){
        goto to;
    }else{
        do{
            SUM1=sum1;
            sum1=sum-SUM1;
            sum=sum+sum1;
            i++;
        }while(i!=month);
        printf("%d",sum);
    }
    return 0;
} 