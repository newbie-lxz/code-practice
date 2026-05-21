#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num;
    scanf("%d",&num);
    if(num<0){
        printf("fu ");
        num=-num;
    }
    int a=0;
    int b=0;
    int sum=0;
    do{
        a=num%10;
        sum=10*sum+a;
        num/=10;
    }while(num>0);
    do{
        b=sum%10;
        sum/=10;
    switch(b){
        case 0:
        printf("ling");
        break;
         case 1:
        printf("yi");
        break;
         case 2:
        printf("er");
        break;
         case 3:
        printf("san");
        break;
         case 4:
        printf("si");
        break;
         case 5:
        printf("wu");
        break;
         case 6:
        printf("liu");
        break;
         case 7:
        printf("qi");
        break;
         case 8:
        printf("ba");
        break;
         case 9:
        printf("jiu");
        break;
    }
    if(sum>0){
    printf(" ");
    }
    }while(sum>0);
    printf(".");
    printf("\n");
    system("pause");
    return 0;
}