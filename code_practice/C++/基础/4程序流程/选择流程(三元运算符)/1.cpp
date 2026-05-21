#include<iostream>
using namespace std;
int main()
{
    int a = 10;
    int b = 20;
    int c;
    c = a > b ? a : b;
    a > b ? a : b = 100;
    //可以给其他变量赋值，也可以用来给自己赋新的值
    cout << c << endl;
    cout << a << endl;
    cout << b << endl;
    return 0;
}