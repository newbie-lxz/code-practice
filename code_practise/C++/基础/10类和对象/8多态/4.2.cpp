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
        //纯虚析构       此处只是一个声明，必须要有具体实现(如果父类开辟到堆区等)
        virtual ~Base() = 0;
};

Base::~Base()
{
    cout<<"Base-----------------------析构"<<endl;
}

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
    //抽象类不能直接实例化对象，但可以声明指向抽象类的指针或引用
    son->speak();
    delete son;
    son = NULL;
}

int main()
{
    test01();
    return 0;
}