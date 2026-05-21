#include<stdio.h>
int main()
{
    int n,x;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        for(int n=2;n<i;n++){
            if(i%n==0){
                x=0;
                break;
            }else{
                x=1;
            }
        }
        if(x==1){
            int a=i+2;
            for(int n=2;n<a;n++){
            if(a%n==0){
                x=0;
                break;
            }else{
                x=1;
            }
        }
        if(x==1){
            printf("%d,%d ",i,a);
        }
    }
    } 
    return 0;
}