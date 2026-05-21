#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

/*
find_if
功能描述：
按条件查找元素

函数原型：
find_if(iterator beg, iterator end, _Pred);
按条件查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
beg：开始迭代器
end：结束迭代器
_Pred：函数或谓词（返回 bool 类型的仿函数）
*/

class Greater5
{
    public:
        bool operator()(int val)
        {
            return val>5;
        }
};

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }

    vector<int>::iterator pos = find_if(v.begin(),v.end(),Greater5());
    if(pos==v.end())
    {
        cout<<"not find"<<endl;
    }
    else
    {
        cout<<"find it "<<*pos<<endl;
    }
}

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

class Greater19
{
    public:
        bool operator()(Person &p)
        {
            return p.m_age > 19;
        }
};

void test02()
{   
    vector<Person> v;
    Person p1("lxz",20);
    Person p2("gxy",19);
    Person p3("jcf",18);
    Person p4("kdz",19);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    vector<Person>::iterator pos = find_if(v.begin(),v.end(),Greater19());
    if(pos==v.end())
    {
        cout<<"not find"<<endl;
    }
    else
    {
        cout<<"find it "<<pos->m_name<<" "<<pos->m_age<<endl;
    }
}

int main()
{
    test01();
    test02();
    return 0;
}