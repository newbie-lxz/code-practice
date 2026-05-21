#include<iostream>
// #include<string>

using namespace std;
//关系运算符重载:大于号，小于号，等于号，不等于号~
class person
{
    public:
        person(string name, int age)
        {
            m_name = name;
            m_age = age;
        }
        
        bool operator==(person &p)
        {
            if(this->m_name == p.m_name && this->m_age == p.m_age)
            {
                return true;
            }
            return false;
        }
        bool operator!=(person &p)
        {
            if(this->m_name == p.m_name && this->m_age == p.m_age)
            {
                return false;
            }
            return true;
        }

        string m_name;
        int m_age;
};

void test01()
{
    person p1("李熙正",19);
    person p2("郭昕妍",19);
    person p3("李熙正",19);
    if(p1==p3)
    {
        cout<<"p1与p3相等"<<endl;
    }

    if(p1!=p2)
    {
        cout<<"p1与p2不相等"<<endl;
    }
}

int main()
{
    test01();
    return 0;
}