#include<iostream>
#include<set>
using namespace std;

/*
set插入数据同时会返回插入结果，表示插入是否成功
multiset不会检测数据，因此可以插入重复数据
*/

void test01()
{
    set<int> s1;

    pair<set<int>::iterator, bool> ret = s1.insert(10);
    if(ret.second)
    {
        cout<<"success"<<endl;
    }
    else
    {
        cout<<"failure"<<endl;
    }

    ret = s1.insert(10);
    if(ret.second)
    {
        cout<<"success"<<endl;
    }
    else
    {
        cout<<"failure"<<endl;
    }

    multiset<int> ms;
    ms.insert(10);
    ms.insert(10);

    for(multiset<int>::iterator msit = ms.begin(); msit != ms.end(); msit++)
    {
        cout<<*msit<<" ";
    }
    cout<<endl;
}

int main()
{
    test01();
    return 0;
}