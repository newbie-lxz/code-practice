#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
函数原型：
set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
求两个集合的  交集
注意：两个集合必须是有序序列
beg1 容器1开始迭代器
end1 容器1结束迭代器
beg2 容器2开始迭代器
end2 容器2结束迭代器
dest 目标容器开始迭代器
*/

void print(int v)
{
    cout<<v<<"\t";
}

void test01()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> vtarget;

    for(int i=0; i<10; i++)
    {
        v1.push_back(i);
        v2.push_back(i*2);
    }
    vtarget.resize(min(v1.size(),v2.size()));

    vector<int>::iterator itEnd = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),vtarget.begin());
    for_each(vtarget.begin(),itEnd,print);          
    //如果用vtarget.end()，可能多余空间输出0
}

int main()
{
    test01();
    return 0;
}