#include<stdio.h>//输入年出现该年的日历
int main()
{
    int year,month,n,c,o=0;
    int sum=0;
    do{
        scanf("%d",&year);
        if(year<1900){
            continue;
        }
        break;
    }while(1);
    int month_days[12];
    int day[12];
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
            for(int f=12;f>=1;f--){
                o+=month_days[f-1];
            }
            sum=sum-o;
            for(int u=1;u<=12;u++){
                day[u-1]=month_days[u-1];
                printf("         %d年 %d月        \n",year,u);
                printf(" MON TUE WED THU FRI SAT SUN\n");
                for(int a=1;a<=day[u-1];a++){
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
                printf("\n");
                sum+=day[u-1];
            }
        }
    }
    return 0;
}
