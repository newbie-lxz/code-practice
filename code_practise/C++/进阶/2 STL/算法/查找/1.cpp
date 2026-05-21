/*
find                查找元素
find_if             按条件查找元素
adjacent_find       查找相邻重复元素
binary_search       二分查找法
count               统计元素个数
count_if            按条件统计元素个数
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
/*
find
功能描述：
查找指定元素，找到返回该元素的迭代器，找不到返回结束迭代器 end

函数原型：
find(iterator beg, iterator end, value);
按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
beg：开始迭代器
end：结束迭代器
value：要查找的元素
*/

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }
    
    vector<int>::iterator pos = find(v.begin(),v.end(),5);
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

        bool operator==(const Person &p)
        {
            return this->m_name == p.m_name && this->m_age == p.m_age;
        }

        string m_name;
        int m_age;
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

    Person pp("jcf",18);

    vector<Person>::iterator pos = find(v.begin(),v.end(),pp);
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