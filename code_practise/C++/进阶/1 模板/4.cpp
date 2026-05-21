//模板的局限性
/*
template<typename T>
void f(T a, T b)
{
    a = b
}
如果a,b是数组，就无法实现，或者自定义的一些结构体bulabula
*/

#include<iostream>
#include<string>
using namespace std;

class Person
{
    public:
        Person(string name, int age)
        {
            this->name = name;
            this->age = age;
        }
    
        string name;
        int age;
};

template<typename T>
bool myCompare(T &a, T &b)
{
    if(a == b)
    {
        return true;
    }
    else
    {
        return false; 
    }
}

template<>bool myCompare(Person &a, Person &b)
{
    if(a.name == b.name && a.age == b.age)
    {
        return true; 
    }
    else{
        return false;
    }
}

void test01()
{
    int a = 10;
    int b = 100;

    bool ret  = myCompare(a,b);

    if(ret)
    {
        cout<<"a == b"<<endl;
    }
    else
    {
        cout<<"a != b"<<endl;
    }
}

void test02()
{
    Person p1("lxz",19);
    Person p11("lxz",19);
    Person p2("gxy",19);

    bool ret1 = myCompare(p1,p11);
    if(ret1)
    {
        cout<<"p1 == p11"<<endl;
    }
    else
    {
        cout<<"p1 != p11"<<endl;
    }

    bool ret2 = myCompare(p1,p2); 
    if(ret2)
    {
        cout<<"p1 == p2"<<endl;
    }
    else
    {
        cout<<"p1 != p2"<<endl;
    }
}

int main()
{
    test01();
    test02();                         //没有41-50报错
    return 0;
}