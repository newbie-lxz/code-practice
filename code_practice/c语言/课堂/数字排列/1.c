#include<stdio.h>
int main()
{
    int a=0;
    for(int i=1;i<=4;i++){
        for(int n=1;n<=4;n++){
            for(int m=1;m<=4;m++){
                int num=i*100+n*10+m;
                if(i!=n&&n!=m&&i!=m){
                    printf("%-4d",num);
                    a++;
                }
            }
            
        }
        printf("\n");
    }
    printf("一共有%d个数。",a);
    return 0;
}