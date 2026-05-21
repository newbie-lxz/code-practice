#include<iostream>
using namespace std;
//当子类与父类出现同名成员，如何通过子类对象访问到子类或父类中的同名数据呢？
//访问子类同名成员，直接访问
//访问父类同名成员，需要加作用域
class Base
{
    public:
        Base()
        {
            m_a = 10;
        }
        void func()
        {
            cout<<"Base的func()调用。"<<endl;
        }
        void func(int a)
        {
            cout<<"Base的func(int a)调用。"<<endl;
        }
        void func2()
        {
            cout<<"Base的func2()调用。"<<endl;
        }
        void func2(int a)
        {
            cout<<"Base的func2(int a)调用。"<<endl;
        }
        int m_a;
};

class Son : public Base
{
    public:
        Son()
        {
            m_a = 200;
        }
        void func()
        {
            cout<<"Son的func()调用。"<<endl;
        }
        
        int m_a;
};

//同名属性处理
void test01()
{
    Son s;
    cout<<"m_a = "<<s.m_a<<endl;                    //200;
    cout<<"m_a = "<<s.Base::m_a<<endl;              //100;
}

//同名函数处理
void test02()
{
    Base b;
    b.func();
    Son s;
    s.func();
    s.Base::func();
    //如果子类中出现和父类同名的成员函数，子类的同名函数会隐藏掉父类中所有同名函数，包括重载
    s.Base::func(10);

    s.func2();
    s.func2(10);
    //若子类没有同名函数则可以随意调用父类的
}

int main()
{
    test01();
    test02();
    return 0;
}