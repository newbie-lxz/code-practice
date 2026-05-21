#include<stdio.h>
int main ()
{
    double x;
    scanf("%lf",&x);
    double f;
     if(x>0){
        f=-1;
     }else if(x==0){
        f=0;
     }else
        f=2*x;
        
    printf("%lf\n",f);

    return 0;
}