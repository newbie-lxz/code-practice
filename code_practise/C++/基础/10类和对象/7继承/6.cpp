#include<iostream>
using namespace std;
//继承中同名的静态成员出现同名在子类对象上如何访问
//静态成员和非静态成员出现同名，处理方式一样
//访问子类同名成员，直接访问
//访问父类同名成员，需要加作用域
class Base
{
    public:
        static void func()
        {
            cout<<"Base 下的 static void func() "<<endl;
        }
        static void func(int a)
        {
            cout<<"Base 下的 static void func(int a) "<<endl;
        }
        static void func2()
        {
            cout<<"Base 下的 static void func2() "<<endl;
        }
        static void func2(int a)
        {
            cout<<"Base 下的 static void func2(int a) "<<endl;
        }

        static int m_a;
};
int Base::m_a = 100;   
//类内声明，类外初始化

class Son : public Base
{
    public:
        static void func()
        {
            cout<<"Son 下的 static void func() "<<endl;
        }

        static int m_a;

};
int Son::m_a = 200;

//同名的静态成员属性
void test01()
{
    //通过对象访问
    cout<<"通过对象访问: "<<endl;
    Base b;
    cout<<" Base 下 m_a = "<<b.m_a<<endl;
    Son s;
    cout<<" Son 下 m_a = "<<s.m_a<<endl;
    cout<<" Base 下 m_a = "<<s.Base::m_a<<endl;

    //通过类名访问
    cout<<"通过类名访问: "<<endl;
    cout<<" Son 下 m_a = "<<Son::m_a<<endl;
    cout<<" Base 下 m_a = "<<Son::Base::m_a<<endl;

}

//同名的静态成员函数
void test02()
{
    Son::func();
    Son::Base::func();
    Son::Base::func(10);

    Son::func2();
    Son::func2(10);
}

int main()
{
    test01();
    cout<<endl;
    test02();
    return 0;
}