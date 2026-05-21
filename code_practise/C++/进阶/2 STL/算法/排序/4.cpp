#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
reverse
功能描述：
将容器内元素进行反转

函数原型：
reverse(iterator beg, iterator end);
反转指定范围的元素
beg 开始迭代器
end 结束迭代器
*/

void print(int v)
{
    cout<<v<<" ";
}

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }
    for_each(v.begin(),v.end(),print);
    cout<<endl;

    reverse(v.begin(),v.end());
    for_each(v.begin(),v.end(),print);
    cout<<endl;
}

int main()
{
    test01();
    return 0;
}