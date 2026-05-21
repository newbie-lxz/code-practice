#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
/*
函数原型：
transform(iterator beg1, iterator end1, iterator beg2, _func);
beg1：源容器开始迭代器
end1：源容器结束迭代器
beg2：目标容器开始迭代器
_func：函数或函数对象
*/
class Transform
{
    public:
        int operator()(int v)
        {
            return v+1;
        }
};

class Print
{
    public:
        void operator()(int val)
        {
            cout<<val<<" ";
        }
};

void test01()
{
    vector<int> v;
    for(int i = 0; i < 10; i++ )
    {
        v.push_back(i);
    }
    for_each(v.begin(),v.end(),Print());
    cout<<endl;

    vector<int> v2;
    v2.resize(v.size());
    transform(v.begin(),v.end(),v2.begin(),Transform());

    for_each(v2.begin(),v2.end(),Print());
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}