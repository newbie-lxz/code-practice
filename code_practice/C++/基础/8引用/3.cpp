#include<iostream>
using namespace std;
//引用做函数的返回值
//1不要返回局部变量的引用
// int &test1(){
//     int a=10;
//     return a;
// }

//2函数的调用可以做为左值 
int &test2(){
    static int a = 10;              //要全局变量
    return a;
}
int main(){
    // int &ref = test1();
    // cout<< "ref = "<<ref<<endl;   //第一次结果正确
    // cout<< "ref = "<<ref<<endl;   //第二次结果错误
    int &ref2 = test2();
    cout<< "ref2 = "<<ref2<<endl; //一直正确   
    test2() = 1000;
    cout<< "ref2 = "<<ref2<<endl;//作为左值 
    cout<< "ref2 = "<<test2()<<endl;
    return 0;
}
