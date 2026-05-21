#include<iostream>
using namespace std;
int main(){
    int a = 10,c = 100;
    int &b = a;                 //引用必须初始化，一旦初始化就不可更改
    cout<<a<<"\t"<<b<<endl;
    b=20;
    cout<<a<<"\t"<<b<<endl;
    b=c;                        //这里是赋值操作，不是引用另一个东西
    cout<<a<<"\t"<<b<<endl;
    return 0;
}
//给变量起别名,和指针类似
//数据类型 &别名 = 原名