#include<iostream>
#include<set>
using namespace std;

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
    s1.insert(10);                 
    s1.insert(1);

    if(s1.empty())
    {
        cout<<"s1为空"<<endl;
    }
    else
    {
        cout<<"s1不为空"<<endl;
        cout<<"s1的大小: "<<s1.size()<<endl;                    //输出4，重复的自动没
    }
    
}

void test02()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(10);                 
    s1.insert(1);

    set<int> s2;

    s1.swap(s2);

    printSet(s1);
    printSet(s2);
}

int main()
{
    test01();
    test02();
    return 0;
}