#include<iostream>
#include<string>

using namespace std;
//函数调用运算符()重载
//由于重载后使用的方式非常像函数的调用，因此被称为仿函数(重载小括号)
//仿函数没有固定写法，非常灵活
class Myprint
{
    public:
        void operator()(string text)
        {
            cout<<text<<endl;
        }


};

class Myadd
{
    public:
        int operator()(int num1, int num2)
        {
            return num1+num2;
        }
};

void Myprint2(string text)
{
    cout<<text<<endl;
}

void test01()
{
    Myprint myprint;
    Myprint()("hello world");                           //匿名函数对象，用完立刻被释放 
    myprint("hello world");                             //仿函数
    Myprint2("hello world");                            //函数
}

void test02()
{
    Myadd myadd;
    cout<<myadd(520, 1314)<<endl;
    cout<<Myadd()(1314,520)<<endl;                      //匿名函数对象，用完立刻被释放 
}


int main()
{
    test01();
    test02();
    return 0;
}