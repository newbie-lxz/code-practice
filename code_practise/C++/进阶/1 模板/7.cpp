//类模板成员函数类外实现
#include<iostream>
#include<string>
using namespace std;


template<class T1, class T2>
class Person
{
    public:
        Person(T1 name, T2 age);
        // {
        //     this->m_age = age;
        //     this->m_name = name;
        // }类内实现

        void showPerson();
        // {
        //     cout<<"name : " <<m_name<<"\t"<<"age : "<<m_age<<endl;
        // }

        T1 m_name;
        T2 m_age;
};

//构造函数的类外实现
template<class T1, class T2>
Person<T1,T2>::Person(T1 name, T2 age)
{
    this->m_age = age;
    this->m_name = name;
}

//成员函数的类外实现                    
template<class T1, class T2>        
void Person<T1,T2>::showPerson()    //因为是类模板里的成员函数所以也要这个，即使它没用T1T2
{
    cout<<"name : " <<m_name<<"\t"<<"age : "<<m_age<<endl;
}

void test()
{
    Person<string,int> p("lxz",19);
    p.showPerson();
}

int main()
{
    test();
    return 0;
}