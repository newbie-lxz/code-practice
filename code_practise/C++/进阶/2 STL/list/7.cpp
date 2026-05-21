#include<iostream>
#include<list>
#include<string>
#include<algorithm>
using namespace std;

class Person
{
    public:
        Person(string name, int age, int height)
        {
            this->m_Age = age;
            this->m_Height = height;
            this->m_Name = name;
        }

        string m_Name;
        int m_Age;
        int m_Height;
};

bool myCompare(Person &v1, Person &v2)
{
    if(v1.m_Age != v2.m_Age)
    {
        return v1.m_Age < v2.m_Age;
    }
    else
    {
        return v1.m_Height > v2.m_Height;
    }
}

void print_List(const list<Person> &L)
{
    for(list<Person>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout<<"姓名: "<<(*it).m_Name<<"\t年龄: "<<(*it).m_Age<<"\t身高: "<<(*it).m_Height<<endl;
    }
    cout<<endl;
}

void test01()
{
    Person p1("lxz",19,191);
    Person p2("gxy",19,168);
    Person p3("kdz",19,178);
    Person p4("cyq",20,182);
    Person p5("jcf",18,185);

    list<Person> l;
    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);
    l.push_back(p4);
    l.push_back(p5);

    l.sort(myCompare);

    print_List(l);
}

int main()
{
    test01();
    return 0;
}