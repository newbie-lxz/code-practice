#include<iostream>
#include<list>


using namespace std;

/*
函数原型：
list<T>lst;                 小ist采用采用模板类实现，对象的默认构造形式：
list(beg,end);              构造函数将[beg,end)区间中的元素拷贝给本身。
list(n,elem);               构造函数将n个elem拷贝给本身。
list(const list &lst);      拷贝构造函数。
*/

void print_List(const list<int> &L)
{
    for(list<int>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void test01()
{
    list<int> L1;
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);

    print_List(L1);

    list<int> L2(L1.begin(), L1.end());
    print_List(L2);

    list<int> L3(L2);
    print_List(L3);

    list<int>L4(10,1000);
    print_List(L4);
}

int main()
{
    test01();
    return 0;
}