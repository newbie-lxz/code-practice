#include<stdio.h>
int main()
{
    long int x,y,time,X,Y;
    scanf("%ld",&time);
    x=time;
    y=2*time;
    if((x/1280)%2==0){
        X=x%1280;
    }else{
        X=1280-x%1280;
    }
     if((y/768)%2==0){
        Y=y%768;
    }else{
        Y=768-y%768;
    }
    printf("(%ld %ld)",X,Y);
    return 0;
} 