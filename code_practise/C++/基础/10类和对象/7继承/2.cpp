#include<iostream>
using namespace std;
//继承方式   对应三种权限
/*
公共继承
保护继承
私有继承
*/
class Base
{
    public:
        int m_a;

    protected:
        int m_b;

    private:
        int m_c;
};

class Son1 : public Base
{
    public:
        void func()
        {
            m_a = 10;                   //父类中的公共权限成员，到子类中依然是公共权限
            m_b = 20;                   //父类中的保护权限成员，到子类中依然是保护权限
            //m_c = 10;                   父类中的私有权限成员，到子类中依然是私有权限，不能访问
        }
};

class Son2 : protected Base
{
    public:
        void func()
        {
            m_a = 100;                  //父类中的公共权限成员，到子类中是保护权限
            m_b = 1000;
            //m_c = 10000;              
        }
};

class Son3 : private Base
{
    public:
        void func()
        {
            m_a = 2;                    //
            m_b = 6;                    //俩都是son3里的私有权限
            //m_c= 99;
        }
};

class grandson : public Son3
{
    public:
        void func()
        {
            //一个都无法操作，因为在son3中都变成私有了
        }

};

void test01()
{
    Son1 s1;
    s1.m_a = 100;
    //其他俩类外不可以访问
    Son2 s2;
    //s2.m_a = 22;
    //m_a因为在父类是公共权限所以显示，但在子类变成保护权限不可操作
    //其他俩类外不可以访问
    Son3 s3;
    //s3.m_a = 33;
    //m_a因为在父类是公共权限所以显示，但在子类变成私有权限不可操作
    //m_b也变成私有权限，m_c老样子
}


int main()
{
    test01();
    return 0;
}