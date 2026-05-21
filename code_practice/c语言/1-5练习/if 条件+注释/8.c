#include<stdio.h>
int main()
{//初始化
double  price=0;
double  bill=0;
//读入金额和票面
printf ("请输入价格：");
scanf("%lf",&price );
printf ("请输入票面：");
scanf("%lf",&bill);
//计算
if (bill>=price){
    printf("应该找您：%lf\n",bill-price);
}
if (bill<price){
    printf("您支付的钱不够，还差：%lf\n",price-bill);
}
return 0;    
}