#include<iostream>
using namespace std;
//运算符重载:对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型
//加号运算符重载:实现两个自定义数据类型相加的运算

class person
{
    public:
    //1 成员函数重载+号    
        // person operator+(person &p)
        // {
        //     person temp;
        //     temp.m_A = this->m_A + p.m_A;
        //     temp.m_B = this->m_B + p.m_B;
        //     return temp;
        // }
        int m_A;
        int m_B;
};

//2 全局函数重载+号
person operator+(const person &p1, const person &p2)       //要用const 类型支持临时变量的传递，因为p1 + p2返回一个临时变量，还要再 + p3，如果没有const就报错
{
    person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}
//两个方法不能同时用

 //运算符重载 也可以发生函数重载
//函数重载的版本
person operator+(person &p1, int num)
{
    person temp;
    temp.m_A = p1.m_A + num;
    temp.m_B = p1.m_B + num;
    return temp;
}

void test01()
{
    person p1,p2;
    p1.m_A = 10;
    p1.m_B = 20;
    p2.m_A = 30;
    p2.m_B = 40;
    //方法1的本质   person p3 = p1.operator+(p2);
    //方法2的本质   person p3 = operator+(p1,p2);
    person p3 = p1 + p2;                //operator+ 简化为 +
    p3 = p1 + p2 + p3;
    person p4 = p1 + 10;
    cout<<"p3.m_A = "<<p3.m_A<<endl;
    cout<<"p3.m_B = "<<p3.m_B<<endl;
}

int main()
{
    test01();
    return 0;
}