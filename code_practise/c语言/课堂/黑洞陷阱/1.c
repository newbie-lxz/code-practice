#include<stdio.h>
int main()
{
    int n,a,b,c,MAX,MIN,N;
    do{
        TO:
        printf("请输入一个小于1000且数字不完全相等正整数:\n");
        scanf("%d",&n);
    }while(n<=0||n>=1000);
    a=n%10;
    b=((n-a)/10)%10;
    c=(n-a-10*b)/100;
    if(a==b&&a==c){
        goto TO;
    }
    N=n;
    do{
        a=N%10;
        b=((N-a)/10)%10;
        c=(N-a-10*b)/100;
        int max,min,mid;
        if(a>=b&&a>=c){
            max=a;
            if(b>=c){
                mid=b;
                min=c;
            }else{
                mid=c;
                min=b;
            }
        }else if(b>=a&&b>=c){
            max=b;
            if(a>=c){
                mid=a;
                min=c;
            }else{
                mid=c;
                min=a;
            }
        }else if(c>=a&&c>=b){
            max=c;
            if(b>=a){
                mid=b;
                min=a;
            }else{
                mid=a;
                min=b;
            }
        }
        MAX=max*100+mid*10+min;
        MIN=min*100+mid*10+max;
        N=MAX-MIN;
        printf("%d-%d=%d\n",MAX,MIN,N);
    }while(N!=495);
    return 0;
}