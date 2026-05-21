#include<stdio.h>
int main()
{
    int A;
    printf("请输入一个小于6正整数A:");
    scanf("%d", &A);
    int n=0;
    
    for(int i=A; i<=A+3; i++){
        for(int j=A; j<=A+3; j++){
            for(int k=A; k<=A+3; k++){
                if(i!=j&&i!=k&&j!=k){
                printf("%d%d%d",i,j,k);
                n++;
                if(n%6!=0){
                    printf(" ");
                }else{
                    printf("\n");
                }
                }
            }
        }
    }
    return 0;
}