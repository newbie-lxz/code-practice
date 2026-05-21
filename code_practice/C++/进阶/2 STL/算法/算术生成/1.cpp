#include<iostream>
#include<numeric>
#include<vector>

using namespace std;

/*
accumulate
功能描述：
计算区间内容器元素累计总和

函数原型：
accumulate(iterator beg, iterator end, value);
计算容器元素累计总和
beg 开始迭代器
end 结束迭代器
value 起始值
*/

void test01()
{
    vector<int> v;
    for(int i=0; i<=100; i++)
    {
        v.push_back(i);
    }
    int num = accumulate(v.begin(),v.end(),0);
    cout<<num<<endl;
}

int main()
{
    test01();

    return 0;
}