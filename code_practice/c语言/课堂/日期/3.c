#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a,b,c;
    int sum=0;
    printf("请输入年月日：");
    scanf("%d %d %d",&a,&b,&c);
    if(a%4==0&&a%400!=0){
        int n;
        sum+=c;
        for(n=b-1;n>=1;n--){
            if(n==1||n==3||n==5||n==7||n==8||n==10){
                sum+=31;
            }else if(n==4||n==6||n==9||n==11){
                sum+=30;
            }else if(n==2){
                sum+=29;
            }
        }
    }else{
        int n;
        sum+=c;
        for(n=b-1;n>=1;n--){
            if(n==1||n==3||n==5||n==7||n==8||n==10){
                sum+=31;
            }else if(n==4||n==6||n==9||n==11){
                sum+=30;
            }else if(n==2){
                sum+=28;
            }
        }
    }
    printf("这是一年中的第%d天",sum);
    system("PAUSE");
    return 0;
}