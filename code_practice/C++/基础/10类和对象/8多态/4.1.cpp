#include<iostream>
#include<string>
using namespace std;
//虚析构和纯虚析构

//多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码
//解决方法：将父类中的析构函数改为虚析构或纯虚析构

//两者共性：
//可以解决父类指针释放子类对象
//都需要具体的函数实现
//区别：
//如果是纯虚析构，该类属于抽象类，无法实例化对象

//虚析构语法    virtual ~类名(){}
//纯虚析构语法  virtual ~类名() = 0;

class Base
{
    public:
        Base()
        {
            cout<<"Base-----------------------构造"<<endl;
        }
        virtual void speak() = 0;
        //利用虚析构解决父类指针释放子类对象时不干净的问题
        virtual ~Base()
        {
            cout<<"Base-----------------------析构"<<endl;
        }
};

class Son : public Base
{
    public:
        Son(string name)
        {
            cout<<"Son-----------------------构造"<<endl;
            m_Name = new string(name);
        }
        void speak()
        {
            cout<<*m_Name<<": 你叫你妈啊。"<<endl;
        }
        ~Son()
        {
            if(m_Name != NULL)
            {
                cout<<"Son-----------------------析构"<<endl;
                delete m_Name;
                m_Name = NULL;
            }
        }
        string *m_Name;
};

void test01()
{
    Base *son = new Son("Tom");             //必须要有(“Tom”)
    son->speak();
    //指针是父类的，父类指针在析构时不会调用子类中的析构函数，导致子类如果有堆区属性，会出现内存泄漏
    //解决办法为在第27行前加上virtual
    delete son;
    son = NULL;
}

int main()
{
    test01();
    return 0;
}