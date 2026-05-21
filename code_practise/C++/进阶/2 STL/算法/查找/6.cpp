#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
/*
count_if
功能描述：
按条件统计元素个数

函数原型：
count_if(iterator beg, iterator end, _Pred);
按条件统计元素出现次数
beg：开始迭代器
end：结束迭代器
_Pred：谓词（返回 bool 类型的函数或仿函数）
*/

class Greater2
{
    public:
        bool operator()(int val)
        {
            return val>2;
        }
};

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

class AgeGreater19
{
    public:
        bool operator()(const Person &val)
        {
            return val.m_age>19;
        }
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

    int ret = count_if(v.begin(),v.end(),Greater2());
    cout<<ret<<endl;
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

    int ret = count_if(v.begin(),v.end(),AgeGreater19());
    cout<<ret<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}