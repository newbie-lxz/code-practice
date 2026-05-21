#include<iostream>
#include<list>

using namespace std;

/*
函数原型：
assign(beg, end);                       将[beg,end)区间中的数据拷贝赋值给本身。
assign(n, elem);                        将n个elem拷贝赋值给本身。
list& operator=(const list &lst);       重载等号操作符
swap(lst);                              将lst与本身的元素互换。
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
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);

    list<int> l2;
    l2 = l1;
    print_List(l2);

    list<int> l3;
    l3.assign(l2.begin(), l2.end());
    print_List(l3);

    list<int> l4;
    l4.assign(10,100);
    print_List(l4);
}

void test02()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);

    list<int> l2;
    l2.assign(10,100);

    print_List(l1);
    print_List(l2);
    l2.swap(l1);
    print_List(l1);
    print_List(l2);
}

int main()
{
    test01();
    test02();
    return 0;
}