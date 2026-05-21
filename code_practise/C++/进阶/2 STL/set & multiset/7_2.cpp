#include<iostream>
#include<set>
#include<string>
using namespace std;

class Person
{
    public:
        Person(string name, int age)
        {
            this->m_name = name;
            this->m_age = age;
        }

        string m_name;
        int m_age;
};
class MyCompare
{
    public:
        bool operator()(Person p1, Person p2)
        {
            if(p1.m_age > p2.m_age)
            {
                return true;
            }
            else if(p1.m_age == p2.m_age && p1.m_name > p2.m_name)
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
};

void printSet(const set<Person, MyCompare> &s)
{
    for(set<Person, MyCompare>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        cout<<(*it).m_name<<"\t"<<(*it).m_age<<endl;
    }
}

void test01()
{
    set<Person,MyCompare> s1;
    Person p1("lxz",20);
    Person p2("gxy",19);
    Person p3("kdz",20);
    Person p4("jcf",18);
    s1.insert(p1);
    s1.insert(p2);
    s1.insert(p3);
    s1.insert(p4);

    printSet(s1);
}

int main()
{
    test01();
    return 0;
}