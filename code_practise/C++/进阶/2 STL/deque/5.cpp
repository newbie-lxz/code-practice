#include<iostream>
#include<deque>
using namespace std;

/*
函数原型：
at(int idx);            返回索引 idx 所指的数据
operator[];             返回索引 idx 所指的数据
front();                返回容器中第一个数据元素
back();                 返回容器中最后一个数据元素
示例：
*/

void printDeque(const deque<int>&d)
{
    for(deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void test01()
{
    deque<int> d1;
    d1.push_back(10);
    d1.push_back(20);
    d1.push_back(30);
    d1.push_front(100);
    d1.push_front(200);
    d1.push_front(300);

    for(int i = 0; i < d1.size(); i++)
    {
        cout<<d1[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i < d1.size(); i++)
    {
        cout<<d1.at(i)<<" ";
    }
    cout<<endl;

    cout<<d1.front()<<endl;
    cout<<d1.back()<<endl;
}


int main()
{
    test01();
    return 0;
}