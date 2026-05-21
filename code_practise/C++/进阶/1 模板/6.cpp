//类模板与继承
/*
1 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中的类型
2 如果不指定，编译器无法给子类分配内存
3 如果想灵活指定出父类中T的类型，子类也需要变为类模板
*/
#include<iostream>
#include<string>
#include<typeinfo>
using namespace std;

template<class T>
class Base
{
    T m;
};

//class Son : public Base         //错误，必须知道父类中的T类型才能继承给子类
class Son : public Base<int>
{

};

void test01()
{
    Son s1;
}

//如果想灵活指定父类中T类型，子类也需要变成类模板
template<class T1, class T2>
class Son2 : public Base<T2>
{
    public:
        Son2()
        {
            cout<<"T1 is " << typeid(T1).name()<<endl;
            cout<<"T2 is " << typeid(T2).name()<<endl;
        }

        T1 obj;
};

void test02()
{
    Son2<int, char>S2;
    //char先告诉30行的T2的类型，再告诉31行继承的父类的类型
}

int main()
{
    //test01();
    test02();
}