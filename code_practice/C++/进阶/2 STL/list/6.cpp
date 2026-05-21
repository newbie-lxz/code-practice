#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

void print_List(const list<int> &L)
{
    for(list<int>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

bool myCompare(int v1, int v2)
{
    //降序    让第一个数大于第二个数
    return v1>v2;
}

void test01()
{
    list<int> L1;
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);
    L1.push_back(50);    

    L1.reverse();
    print_List(L1);
}

void test02()
{
    list<int> L1;
    L1.push_back(100);
    L1.push_back(20);
    L1.push_back(310);
    L1.push_back(400);
    L1.push_back(150);      
    print_List(L1);
    //所有不支持随机访问迭代器的容器，不可以用标准算法
    //不支持随机访问迭代器的容器,内部会提供对应的一些算法
    //sort(L1.begin(), L1.end());

    L1.sort();              //默认从小到大  升序
    print_List(L1);
    
    L1.sort(myCompare);
    print_List(L1);
}

int main()
{
    test01();
    test02();
    return 0;
}