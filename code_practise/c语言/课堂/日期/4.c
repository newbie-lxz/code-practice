#include<stdio.h>
#include<stdlib.h>
int main()
{
    printf("请输入两个日期:(大日期):xxxx xx xx (小日期):xxxx xx xx\n");
    int a1,a2,b1,b2,c1,c2;
    int sum1=0,sum2=0,sum3=0;
    scanf("%d %d %d",&a1,&b1,&c1);
    scanf("%d %d %d",&a2,&b2,&c2);
    if(a1%4==0&&a1%400!=0){
        int n1;
        sum1+=c1;
        for(n1=b1-1;n1>=1;n1--){
            if(n1==1||n1==3||n1==5||n1==7||n1==8||n1==10){
                sum1+=31;
            }else if(n1==4||n1==6||n1==9||n1==11){
                sum1+=30;
            }else if(n1==2){
                sum1+=29;
            }
        }
    }else{
        int n1;
        sum1+=c1;
        for(n1=b1-1;n1>=1;n1--){
            if(n1==1||n1==3||n1==5||n1==7||n1==8||n1==10){
                sum1+=31;
            }else if(n1==4||n1==6||n1==9||n1==11){
                sum1+=30;
            }else if(n1==2){
                sum1+=28;
            }
        }
    }
    if(a2%4==0&&a2%400!=0){
        int n2;
        sum2+=c2;
        for(n2=b2-1;n2>=1;n2--){
            if(n2==1||n2==3||n2==5||n2==7||n2==8||n2==10){
                sum2+=31;
            }else if(n2==4||n2==6||n2==9||n2==11){
                sum2+=30;
            }else if(n2==2){
                sum2+=29;
            }
        }
    }else{
        int n2;
        sum2+=c2;
        for(n2=b2-1;n2>=1;n2--){
            if(n2==1||n2==3||n2==5||n2==7||n2==8||n2==10){
                sum2+=31;
            }else if(n2==4||n2==6||n2==9||n2==11){
                sum2+=30;
            }else if(n2==2){
                sum2+=28;
            }
        }
    }
    int n;
    for(n=a1-1;n>=a2;n--){
        if(n%4==0&&n%400!=0){
            sum3+=366;
        }else{
            sum3+=365;
        }
    }
    sum3+=sum1-sum2;
    printf("相差%d天",sum3);
    system("PAUSE");
    return 0;
}