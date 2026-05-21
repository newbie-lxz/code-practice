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

class Mycompare
{
    public:
        bool operator()(int v1, int v2)
        {
            return v1>v2;
        }
};

void test01()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(300);
    s1.insert(40);                 
    s1.insert(1);

    printSet(s1);

    //更改排序规则
    set<int, Mycompare> s2;
    s2.insert(1);
    s2.insert(2);
    s2.insert(89);
    s2.insert(34);
    s2.insert(-1);

    for(set<int,Mycompare>::const_iterator it = s2.begin(); it != s2.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl; 
}

int main()
{
    test01();
    return 0;
}