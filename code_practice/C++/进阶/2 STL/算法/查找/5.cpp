#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

/*
count
功能描述：
统计元素个数

函数原型：
count(iterator beg, iterator end, value);
统计元素出现次数
beg：开始迭代器
end：结束迭代器
value：要统计的元素
*/

class Person
{
    public:
        Person(string name, int age)
        {
            this->m_name = name;
            this->m_age = age;
        }

        bool operator==(const Person &p)            //必须有const
        {
           if(this->m_age == p.m_age) 
           {
                return true;
           }
           else
           {
                return false; 
           }
        }

        string m_name;
        int m_age;
};

void test01()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(0);
    v.push_back(4);
    v.push_back(4);
    v.push_back(0);
    int ret = count(v.begin(),v.end(),0);
    cout<<"0 is "<<ret<<endl;
}

void test02()
{
    vector<Person> v;
    Person p1("lxz",20);
    Person p2("gxy",19);
    Person p3("kdz",19);
    Person p4("jcf",18);
    Person p5("gxy",19);
    Person p6("gxy",19);
    Person p7("lxz",20);
    Person p8("lxz",20);
    Person p9("kdz",19);
    Person p10("lxz",20);
    Person p11("lxz",20);
    Person p12("jcf",18);
    Person p13("lxz",20);
    Person p14("gxy",19);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);
    v.push_back(p7);
    v.push_back(p8);
    v.push_back(p9);
    v.push_back(p10);
    v.push_back(p11);
    v.push_back(p12);
    v.push_back(p13);
    v.push_back(p14);

    Person p("lxz",20);
    int ret = count(v.begin(),v.end(),p);
    cout<<ret<<endl;  
}

int main()
{
    test01();
    test02();
    return 0;
}