/*
普通函数和函数模板的调用规则
1 如果函数模板和普通函数都可以实现，优先调用普通函数
2 可以通过空模板参数列表强制调用函数模板
3 函数模板也可以发生重载
4 如果函数模板可以发生更好的匹配，优先调用函数模板
*/

#include<iostream>
using namespace std;

void myPrint(int a, int b)
{
    cout<<"普通函数调用。"<<endl;
}

template<typename T>
void myPrint(T a, T b)
{
    cout<<"函数模板调用。"<<endl;
}

template<typename T>
void myPrint(T a, T b, T c)
{
    cout<<"重载的函数模板调用。"<<endl;
}

void test01()
{
    int a = 10;
    int b = 20;
    myPrint(a,b);                       //调用普通函数, 如果把13-15行注释掉，只留下函数声明，则是报错也不会调用函数模板

    char A = 'a';
    char B = 'b';
    myPrint(A,B);                       //调用函数模板，因为更好匹配
}

void test02()
{
    int a = 10;
    int b = 20;
    myPrint<>(a,b);                     //调用函数模板
    myPrint(a,b,100);                   //调用重载的函数模板
}

int main()
{
    test01();
    test02();
    return 0;
}