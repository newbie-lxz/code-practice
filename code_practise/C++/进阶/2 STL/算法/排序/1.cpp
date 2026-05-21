#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;

/*
sort
功能描述：
对容器内元素进行排序

函数原型：
sort(iterator beg, iterator end, _Pred);
按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
beg 开始迭代器
end 结束迭代器
_Pred 谓词
*/

void print(int val)
{
    cout<<val<<" ";
}

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(60);
    v.push_back(50);
    v.push_back(40);

    sort(v.begin(),v.end());
    for_each(v.begin(),v.end(),print);
    cout<<endl;

    sort(v.begin(),v.end(),greater<int>());
    //sort(v.rbegin(),v.rend());
    for_each(v.begin(),v.end(),print);
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}