#include<iostream>
using namespace std;
//子类继承父类后，当创建子类对象，也会调用父类的构造函数
//继承中的构造与析构顺序
class Base
{
    public:
        Base()
        {
            cout<<"Base的构造函数!"<<endl;                      //(1)
        }
        ~Base()
        {
            cout<<"Base的析构函数!"<<endl;                      //(2)
        }
};

class Son : public Base
{
    public:
       Son()
       {
            cout<<"Son的构造函数!"<<endl;                       //(3)
       } 
       ~Son()
       {
            cout<<"Son的析构函数!"<<endl;                       //(4)
       }
};

void test01()
{
    Base b1;
}

void test02()
{
    Son s;
}

int main()
{
    test01();
    test02();
    return 0;
}
//输出顺序(1)(2)(1)(3)(4)(2)