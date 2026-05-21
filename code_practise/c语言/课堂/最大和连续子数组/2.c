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
    unsigned length;
    long sum=0;
    printf("请输入数组长度: length(0<length<10001):\n");
    scanf("%u",&length);
    int num[length];
    printf("请输入数值n(-100<=n<=100)");
    for(int i=0;i<length;i++){
        scanf("%d",&num[i]);
    }
    order(num,length);
    for(int i=0;i<length;i++){
        if(num[i]>0){
            sum+=num[i];
        }
    }
    if(sum==0){
        sum=num[length-1];
    }
    printf("\n%d",sum);
    return 0;
}