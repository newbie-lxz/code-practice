#include<iostream>
#include<set>
using namespace std;
//所有元素都会在插入时自动被排序
//set/multiset属于关联式容器，底层结构是用二叉树实现
//set不允许容器有重复的元素，multiset允许
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
    s1.insert(10);                      //重复，不报错，白插
    s1.insert(1);

    printSet(s1);

    set<int> s2(s1);
    printSet(s2);

    set<int> s3 = s2;
    printSet(s3);
}

int main()
{
    test01();
    return 0;
}