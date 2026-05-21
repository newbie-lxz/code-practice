#include<iostream>
#include<queue>
#include<string>

using namespace std;

/*
构造函数：
queue<T> que;                               queue采用模板类实现，queue对象的默认构造形式
queue(const queue &que);                    拷贝构造函数

赋值操作：
queue& operator=(const queue &que);         重载等号操作符

数据存取：
push(elem);                                 往队尾添加元素
pop();                                      从队头移除第一个元素
back();                                     返回最后一个元素
front();                                    返回第一个元素

大小操作：
empty();                                    判断堆栈是否为空
size();                                     返回栈的大小
*/

class Person
{
    public:
        Person(string name, int age)
        {
            this->m_Age = age;
            this->m_Name = name;
        }

        string m_Name;
        int m_Age;
};

void test01()
{
    queue<Person> q;
    Person p1("唐僧", 30);
    Person p2("孙悟空", 800);
    Person p3("猪八戒", 500);
    Person p4("沙和尚", 300);

    q.push(p1);
    q.push(p2);
    q.push(p3);
    q.push(p4);

    while(!q.empty())
    {
        cout<<"队头 --- 姓名： "<<q.front().m_Name<<endl;
        cout<<"队头 --- 年龄： "<<q.front().m_Age<<endl;

        cout<<"队尾 --- 姓名： "<<q.back().m_Name<<endl;
        cout<<"队尾 --- 年龄： "<<q.back().m_Age<<endl;

        q.pop();
    }
}

int main()
{
    test01();
    return 0;
}