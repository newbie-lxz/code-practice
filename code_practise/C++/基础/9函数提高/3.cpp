//函数重载
//定义的函数名字可以相同,作用在同一个作用域
//要求函数参数类型、个数、或者顺序不同
//函数的返回值不作为条件
#include<iostream>
using namespace std;
void func(){
    cout<<"hello world"<<endl;
}
void func(int a){
    cout<<"hello world!"<<endl;
}
void func(double a){
    cout<<"Helloworld"<<endl;
}
void func(double a, int b){
    cout<<"Hello world"<<endl;
}
void func(int a, double b){
    cout<<"Hello world!"<<endl;
}
int main(){
    func();
    func(10);
    func(10.0); 
    func(10.0,10);
    func(10,10.0);
    return 0;
}