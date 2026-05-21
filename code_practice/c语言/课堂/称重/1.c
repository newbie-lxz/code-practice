#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    srand((unsigned)time(NULL));
    int x=rand()%13;
    int ball[13];
    int i;
    ball[x]=rand()%2+1;
    printf("第%d个球是异常球,",x+1);
    if(ball[x]==2){
        for(i=0;i<13;i++){
            if(i!=x){
                ball[i]=1;
            }
        }
        printf("异常球偏重");
    }else{
        for(i=0;i<13;i++){
            if(i!=x){
                ball[i]=2;
            }
        }
        printf("异常球偏轻");
    }
    printf("\n");
    int sum1,sum2;
    printf("先将前八个球按1/2/3/4和5/6/7/8分为两组并比较重量\n");
    sum1=ball[1]+ball[2]+ball[3]+ball[0];
    sum2=ball[4]+ball[5]+ball[6]+ball[7];
    if(sum1==sum2){
        printf("如果重量相等,则这8个球都是正常的,异常球在剩下的5个球中。");
        printf("将剩下5个球9/10/11和前8个中的三个比较重量。\n");
        int sum3;
        sum3=ball[9]+ball[8]+ball[10];
        if(sum3==sum1*3/4){
            printf("如果重量相等，则异常球在剩下的两个球中,从中挑出12与之前确定的正常球比较\n");
            if(ball[1]==ball[11]){
                printf("异常球是13号。\n");
            }else{
                printf("异常球是12号。\n");
            }
        }else{
            printf("如果重量不相等则异常球在9/10/11中,再选9/10比较重量。");
            if(ball[8]==ball[9]){
                printf("如果重量相等,则异常球为11号");
            }else{
                if(sum1*3/4>sum3){
                    printf("如果9/10/11的重量和偏轻,则异常球偏轻");
                }else{
                    printf("如果9/10/11的重量和偏重,则异常球偏重");
            }
        }
        if((ball[8]-ball[9])*(sum1*3/4-sum3)>0){
            printf("异常球是10号。\n");
        }else{
            printf("异常球是9号。\n");
        }
        }
    }else{
        printf("如果重量不相等,则剩下的5个球是正常的。");
        printf("从偏重的一组选出编号前3个、偏轻的一组选出编号前2个一共5个球与剩下的5个正常的作比较。\n");
        int sum4;
        int sum5=5*ball[12];
        int sum7=2*ball[12];
        if(sum1>sum2){
            printf("如果1/2/3/4更重,则选出1/2/3/5/6。\n");
            sum4=ball[1]+ball[0]+ball[5]+ball[4]+ball[2];
            if(sum4==sum5){
                printf("如果一样重,那么异常球在4/7/8中\n");
                printf("选择4/7与两个正常球比较。\n");
                int sum6=ball[3]+ball[6];
                if(sum6==sum7){
                    printf("如果重量相等,则异常球是8号");
                }else if(sum6>sum7){
                    printf("如果4/7更重,则异常球是4号");
                }else {
                    printf("如果4/7更轻,则异常球是7号");
                }
            }else if(sum4>sum5){
                printf("如果1/2/3/5/6更重,则异常球在1/2/3中\n");
                printf("选1/2进行比较,");
                if(ball[0]>ball[1]){
                    printf("如果1更重;则异常球是1号");
                }else if(ball[0]<ball[1]){
                    printf("如果2更重;则异常球是2号");
                }else{
                    printf("如果1/2一样重;则异常球是3号");
                }
            }else{
                printf("如果1/2/3/5/6更轻,则异常球在5/6中\n");
                printf("选择5/6进行比较,");
                if(ball[4]<ball[5]){
                    printf("如果5更轻,则异常球是5号");
                }else{
                    printf("如果6更轻,则异常球是6号");
                }
            }
        }else{ 
                printf("如果1/2/3/4更轻,则选出1/2/5/6/7。\n");
                sum4=ball[1]+ball[0]+ball[5]+ball[4]+ball[6];
                if(sum4==sum5){
                    printf("如果一样重,那么异常球在3/4/8中\n");
                    printf("选择4/8与两个正常球比较。\n");
                    int sum6=ball[3]+ball[7];
                    if(sum6==sum7){
                        printf("如果重量相等,则异常球是3号");
                    }else if(sum6>sum7){
                        printf("如果4/8更重,则异常球是8号");
                    }else {
                        printf("如果4/8更轻,则异常球是4号");
                    }
                }else if(sum4>sum5){
                    printf("如果1/2/5/6/7更重,则异常球在5/6/7中\n");
                    printf("选5/6进行比较,");
                    if(ball[4]>ball[5]){
                        printf("如果5更重;则异常球是5号");
}else if(ball[0]<ball[1]){
                        printf("如果6更重;则异常球是6号");
                    }else{
                        printf("如果5/6一样重;则异常球是7号");
                    }
                }else{
                    printf("如果1/2/5/6/7更轻,则异常球在1/2中\n");
                    printf("选择1/2进行比较,");
                    if(ball[4]<ball[5]){
                        printf("如果1更轻,则异常球是1号");
                    }else{
                        printf("如果2更轻,则异常球是2号");
                    }
                }
        }
        
    }
    return 0;
}