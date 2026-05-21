#include<stdio.h>
int main()
{
    int a,b,c,d,e,t;
    int x=0;
    int sum=0;
    scanf("%d %d", &a,&b);
    if(a<b){
        c=a;
        e=b;
    }else{
        c=b;
        e=a;
    }
    if(c==1){
        c=2;
    }
    for(d=c;d<=e;d++){
        int t=1;
        for(int n=2;n<d;n++){
            if(d%n==0){
                t=0;
                break;
            }
        }
        if(t==1){
        x++;
        sum+=d;
        }
    }
    printf("%d %d",x,sum);
    return 0;
}