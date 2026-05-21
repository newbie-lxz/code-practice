#include<iostream>
#include<string>
#include<typeinfo>
using namespace std;

//类模板
//1 指定传入类型
template<class NameType, class AgeType>
class Person
{
    public:
        Person(NameType name, AgeType age)
        {
            this->m_Name = name;
            this->m_Age = age;
        }

        void Print()
        {
            cout<< "name: " << this->m_Name << " age:" <<this->m_Age<<endl;
        }

        NameType m_Name;
        AgeType m_Age;
};

void test01()
{
    Person<string,int>p1("lxz",19);
    p1.Print();
}

//2 参数模板化
template<class T1, class T2>
void printPerson(Person<T1, T2>&p)
{
    p.Print();
    cout<<"T1 is "<<typeid(T1).name()<<endl<<"T2 is "<<typeid(T2).name()<<endl;
    //看这个类型名字(全名)
}

void test02()
{
    Person<string,int>p2("gxy",19);
    printPerson(p2);
}

//3 整个类模板化
template<class T>
void print2(T &p)
{
    p.Print(); 
    cout<<"T is "<<typeid(T).name()<<endl;
}

void test03()
{
    Person<string,int>p2("gxy love lxz",19);
    print2(p2);
}


int main()
{
    test01();
    test02();
    test03();
    return 0;
}