#include<stdio.h>
int main ()
{
    double x;
    int one, two, five;
    int n=0;
    scanf("%lf", &x);

    for(one=1; one<x*10; one++){
        for(two=1; two<x*10/2; two++){
            for(five=1; five<x*10/5; five++){
                if(one*1+two*2+five*5==x*10){
                    printf("可以用%d个一角,%d个两角和%d个五角来付款\n", one,two,five);
                    n++;
                }
            }
        }
    }
    printf("有%d个方法",n);
    return 0;
}