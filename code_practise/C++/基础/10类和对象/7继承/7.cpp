#include<iostream>
using namespace std;
//c++允许一个类继承多个类
//语法   class 子类 : 继承方式 父类1, 继承方式 父类2....
//实际开发不建议这样使用
class Base1
{
    public:
        int m_a;
        int m_A;
        Base1()
        {
            m_a = 100;
            m_A = 666;
        }
};

class Base2
{
    public:
        int m_b;
        int m_A;
        Base2()
        {
            m_b = 200;
            m_A = 999;
        }
};

class Son : public Base1 , public Base2
{
    public:
        int m_c;
        int m_d;
        Son()
        {
            m_c = 300;
            m_d = 400;
        }
};

void test01()
{
    Son s;
    cout<<"sizeof(s) = "<<sizeof(s)<<endl;
    cout<<"m_a = "<<s.m_a<<endl;
    cout<<"m_b = "<<s.m_b<<endl;
    cout<<"m_c = "<<s.m_c<<endl;
    cout<<"m_d = "<<s.m_d<<endl;
    cout<<"Base1 m_A = "<<s.Base1::m_A<<endl;
    cout<<"Base2 m_A = "<<s.Base2::m_A<<endl;
}

int main()
{
    test01();
    return 0;
}