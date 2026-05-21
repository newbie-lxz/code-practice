#include<stdio.h>
int MAX(int a,int b)
{
    if(a>=b){
        return a;
    }else{
        return b;
    }
}

int main()
{   
    unsigned length;
    printf("请输入数组长度: length(0<length<10001):\n");
    scanf("%u",&length);
    int num[length];
    printf("请输入数值n(-100<=n<=100)\n");
    for(int i=0;i<length;i++){
        scanf("%d",&num[i]);
    }
    long sum1=num[0];
    long max1=-100;
    for(int j=1;j<length;j++){
       sum1=MAX(sum1+num[j],num[j]);
       max1=MAX(max1,sum1);
    }
    printf("%ld",max1);
    return 0;
}