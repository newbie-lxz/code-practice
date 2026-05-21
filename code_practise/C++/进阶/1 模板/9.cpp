//类模板与友元
/*
全局函数类内实现  直接在类内声明友元即可
全局函数类外实现，需要提前让编译器直到全局函数的存在  太复杂 不用  P181
*/
#include<iostream>
#include<string>
using namespace std;


template<class T1, class T2>
class Person
{
        friend void showPerson(Person<T1,T2> p)
        {
            cout<<"name : " <<p.m_name<<"\t"<<"age : "<<p.m_age<<endl;
        }               //全局函数类内实现

    public:
        Person(T1 name, T2 age)
        {
            this->m_age = age;
            this->m_name = name;
        }

    private:
        T1 m_name;
        T2 m_age;
};



void test01()
{
    Person<string, int>p("lxz",19);
    showPerson(p);
}

int main()
{
    test01();
    return 0;
}
