#include<iostream>
using namespace std;
//菱形继承or钻石继承
//两个派生类继承同一个基类
//又有某个类同时继承这两个派生类
//
class Animal
{
    public:
        int m_Age;
};

//继承之前加上关键字virtual变为虚继承
//Animal类被称为虚基类
class Sheep : virtual public Animal
{
};

class Camel : virtual public Animal
{
};

class Cnm : public Sheep, public Camel
{
};

//未加virtual 两个年纪都可以用，造成浪费
//加了virtual 以后面的为准，18被28覆盖了，而且可以直接cnm.m_Age不需要再加作用域
// void test01()
// {
//     Cnm cnm;
//     cnm.Sheep::m_Age = 18;
//     cnm.Camel::m_Age = 28;

//     cout<<"Sheep's age = "<<cnm.Sheep::m_Age<<endl;
//     cout<<"Camel's age = "<<cnm.Camel::m_Age<<endl;
// }

void test02()
{
    Cnm cnm;
    cnm.m_Age = 180;
    cout<<"Cnm's age = "<<cnm.m_Age<<endl;

}
int main()
{
    //test01();
    test02();
    return 0;
}