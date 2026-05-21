#include<stdio.h>//输入年和月份出现该月的日历
int main()
{
    int year,month,n,c,o=0;
    int sum=0;
    do{
        scanf("%d %d",&year,&month);
        if(year<1900||month<1||month>12){
            continue;
        }
        break;
    }while(1);
    int month_days[12];
    for(int i=0;i<=(year-1900);i++){
        if(((i+1900) % 4 == 0 && (i+1900) % 100 != 0)||(i+1900) % 400==0 ) {
            month_days[0] = 31; month_days[1] = 29; month_days[2] = 31;
            month_days[3] = 30; month_days[4] = 31; month_days[5] = 30;
            month_days[6] = 31; month_days[7] = 31; month_days[8] = 30;
            month_days[9] = 31; month_days[10] = 30; month_days[11] = 31;
        } else {
            month_days[0] = 31; month_days[1] = 28; month_days[2] = 31;
            month_days[3] = 30; month_days[4] = 31; month_days[5] = 30;
            month_days[6] = 31; month_days[7] = 31; month_days[8] = 30;
            month_days[9] = 31; month_days[10] = 30; month_days[11] = 31;
        } 
        for(int e=1;e<=12;e++){
            sum+=month_days[e-1];
        }
        if(i==year-1900){
            for(int f=12;f>=month;f--){
                o+=month_days[f-1];
            }
            sum=sum-o;
            n=month_days[month-1];
        }
    }
    printf("         %d年 %d月        \n",year,month);
    printf(" MON TUE WED THU FRI SAT SUN\n");
    for(int a=1;a<=n;a++){
        if (a==1){
            c=sum%7;
            for(int b=1;b<=c;b++){
                printf("    ");
            }
            printf("  %d ",a);
        }else if(a<10){
            printf("  %d ",a);
        }else{
            printf("  %d",a);
        }
        if((sum+a)%7==0){
            printf("\n");
        }
    }
    return 0;
}