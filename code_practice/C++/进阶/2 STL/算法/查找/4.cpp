#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
binary_search
功能描述：
查找指定元素是否存在

函数原型：
bool binary_search(iterator beg, iterator end, value);
二分查找法查找指定的元素，查到返回 true，否则返回 false
注意：在无序序列中不可用,默认升序
beg：开始迭代器
end：结束迭代器
*/

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }

    bool ret = binary_search(v.begin(),v.end(),9);
    if(ret)
    {
        cout<<"find it"<<endl;
    }
    else
    {
        cout<<"not find"<<endl;
    }
}

int main()
{
    test01();

    return 0;
}