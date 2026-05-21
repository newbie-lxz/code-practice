#include<algorithm>
#include<vector>
#include<string> 
#include<iostream>
using namespace std;
//vector容器中存放自定义数据类型
class Person
{
    public:
        Person(string name, int age)
        {
            this->m_Name = name;
            this->m_Age = age;
        }

        string m_Name;
        int m_Age;
};

void test01()
{
    vector<Person> v;
    Person p1("lxz",19);
    Person p2("gxy",19);
    Person p3("kdz",19);
    Person p4("cyq",20);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    for(vector<Person>:: iterator i = v.begin(); i < v.end(); i++)
    {
        cout<<"name : "<< (*i).m_Name <<"\t age : "<<i->m_Age<<endl;
    }//跟指针类似
    cout<<endl;
}

//存放自定义数据类型的指针
void test02()
{
    vector<Person*> v; 
    Person p1("lxz",19);
    Person p2("gxy",19);
    Person p3("kdz",19);
    Person p4("cyq",20);
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    for(vector<Person*>:: iterator i = v.begin(); i < v.end(); i++)
    {
        cout<<"name : "<< (**i).m_Name <<"\t age : "<<(*i)->m_Age<<endl;
    }//跟指针类似
    cout<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}