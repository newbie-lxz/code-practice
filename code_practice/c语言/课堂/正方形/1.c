#include<stdio.h>
int main()
{
    printf("请输入一个正整数:");
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        if(i==1||i==n){
            for(int r=1;r<=n;r++){
                printf("*");
                if(r==n){
                    printf("\n");
                }
            }
        }else{
            if(n%2==1&&i==n/2+1){
                for(int r=1;r<=n;r++){
                    if(r==1||r==n||r==n/2+1){
                        printf("*");
                    }else {
                        printf(" ");
                    }
                    if(r==n){
                        printf("\n");
                    }
                }
            }else{
                for(int r=1;r<=n;r++){
                    if(r==1||r==n){
                        printf("*");
                    }else{
                        printf(" ");
                    }
                    if(r==n){
                        printf("\n");
                    }
                }
            }
        }
    }
    return 0;
}