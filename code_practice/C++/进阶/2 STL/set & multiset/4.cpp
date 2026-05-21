#include<iostream>
#include<set>
using namespace std;

/*
find(key);          查找 key 是否存在，若存在，返回该键的元素的迭代器；若不存在，返回 set.end()。
count(key);         统计 key 的元素个数
*/

void printSet(const set<int> &s)
{
    for(set<int>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void test01()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);                 
    s1.insert(1);

    set<int>::iterator pos = s1.find(30);

    if(pos != s1.end())
    {
        cout<<"找到了： "<<*pos<<endl;
    }
    else
    {
        cout<<"未找到。"<<endl;
    }
}

void test02()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);  
    s1.insert(10);               
    s1.insert(1);

    int num = s1.count(10);
    int num2 = s1.count(30);
    int num3 = s1.count(0);

    cout<<"10 : "<<num<<endl;
    cout<<"30 : "<<num2<<endl;
    cout<<"0 : "<<num3<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}