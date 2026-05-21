#include<iostream>
using namespace std;
//纯虚函数和抽象类
//exampleplus的第12行没用，2.cpp的第10行也没用，此时可以改为纯虚函数

class Base
{
    public:
        virtual void func() = 0;
        //纯虚函数： virtual 返回值类型 函数名 (参数列表) = 0；
        //当类中有了纯虚函数，这个类也被称为抽象类
        //抽象类特点：
        //1、无法实例对象
        //2、子类必须重写抽象类中的纯虚函数，否则也属于抽象类

};

class Son : public Base
{
    public:
        void func()
        {
            cout<<"1"<<endl;
        }
};

class Son2 : public Base
{
    public:
    //未重写
};

void test01()
{
    //Base b;      
    //new Base;                         
    //报错，抽象类不允许实例化对象

    //Son2.s;
    //报错，子类必须重写抽象类中的纯虚函数，否则也属于抽象类
    Base *abc = new Son;
    abc->func();
    delete abc;
    abc = NULL;
}

int main()
{
    test01();
    return 0;
} 