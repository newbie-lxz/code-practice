#include<iostream>
using namespace std;
void fun(int &a){
    cout<<"fun(int &a)"<<endl;
}
void fun(const int &a){
    cout<<"fun(const int &a)"<<endl;
}//类型不同

void func(int a){
    cout<<"func(int a)"<<endl;
}
void func(int a, int b=10){
    cout<<"func(int a,int b=10)"<<endl;
}
int main(){
    fun(10);
    int a=10;
    fun(a);//a是变量，优先调用不带const的那一个 
    //func(a);
    //出现错误，因为有默认值，传入时两个形式相同，无法区分
    return 0;
}