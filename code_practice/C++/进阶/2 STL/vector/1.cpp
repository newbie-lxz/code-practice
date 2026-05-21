#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
/*
容器:   vector
算法:   for_each
迭代器: vector<int>::iterator 
*/

void test01()
{
    //创建名为v的vector容器
    vector<int> v;

    //向容器中插入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    //通过迭代器访问容器中的数据
    vector<int>::iterator Begin = v.begin();      //v.begin()  起始迭代器，指向容器中第一个元素
    vector<int>::iterator End = v.end();          //v.end()    结束迭代器，指向容器中最后一个元素的下一个位置

    while(Begin != End)
    {
        cout<<*Begin<<"\t";
        Begin++;
    }
    cout<<endl;
}

void test02()
{
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    for(vector<int>::iterator i = v.begin(); i != v.end(); i++)
    {
        cout<<*i<<"\t";
    }
    cout<<endl;
}

void myPrint(int val)
{
    cout<<val<<"\t";
}

void test03()
{
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    for_each(v.begin(), v.end(), myPrint);          //起点，终点，函数名
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}