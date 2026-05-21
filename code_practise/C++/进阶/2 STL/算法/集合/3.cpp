#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
set_difference
功能描述：
求两个集合的差集

函数原型：
set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
求两个集合的差集
注意：两个集合必须是有序序列
beg1 容器1开始迭代器
end1 容器1结束迭代器
beg2 容器2开始迭代器
end2 容器2结束迭代器
dest 目标容器开始迭代器
*/

void print(int v)
{
    cout<<v<<" ";
}

void test01()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v1target;

    for(int i=0; i<10; i++)
    {
        v1.push_back(i);
        v2.push_back(i*2);
    }

    v1target.resize(max(v1.size(),v2.size()));

    vector<int>::iterator itEnd = set_difference(v1.begin(),v1.end(),v2.begin(),v2.end(),v1target.begin());
    for_each(v1target.begin(),itEnd,print);  
    cout<<endl;

    itEnd = set_difference(v2.begin(),v2.end(),v1.begin(),v1.end(),v1target.begin());
    for_each(v1target.begin(),itEnd,print);  
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}