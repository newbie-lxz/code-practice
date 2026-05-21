#include<stdio.h>
void order(int num[],int n)
{
    int i,j,k,temp;
    for(i=0;i<n-1;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(num[j]<=num[k]){
                k=j;
            }
        }
        if(k!=i){
            temp=num[k];
            num[k]=num[i];
            num[i]=temp;
        }
    }
}

int main()
{   
    int n;
    do{
    printf("请输入输入的数字个数：\n");
    scanf("%d",&n);
    }while(n<1||n>108);
    int num[n];
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        num[i]=a;
    }
    order(num,n);
    for(int j=0;j<n-1;j++){
        if(num[j]<num[j+1]){
            printf("%d  ",num[j]);
        }
        if(j==n-2){
            if(num[n-2]!=num[n-1]){
                printf("%d  ",num[n-1]);
            }
        }
    }
    return 0;
}