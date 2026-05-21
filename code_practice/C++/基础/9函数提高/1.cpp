#include<iostream>
int add(int a, int b=10, int c=100){
    return a+b+c;
}//形参可以有初始值
//前面形参有初始值的后面的形参也必须要有，不能b有c没有  
//int add(int a, int b=10, int c);这就是错的

int add2(int a=10, int b=10);//声明有初始值
int main(){
    add(10);
    add(10,10,10);//传了数据就用自己的，没传用默认的
    return 0;
}
int add2(int a, int b)//实现就不能有 
{
    return a+b;
}//声明与实现只能有一个初始化，可以是声明也可以是实现