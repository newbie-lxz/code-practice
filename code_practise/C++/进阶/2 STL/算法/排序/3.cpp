#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
merge
功能描述：
两个容器元素合并，并存储到另一容器中

函数原型：
merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
容器元素合并，并存储到另一容器中
注意：两个容器必须是有序的,同序，同为降序需要更换比较谓词greater<>
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

    for(int i=0; i<10; i++)
    {
        v1.push_back(i);
        v2.push_back(i*2-3);
    }

    vector<int> target;
    target.resize(v1.size()+v2.size());
    
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),target.begin());
    for_each(target.begin(),target.end(),print);
    cout<<endl;
}

int main()
{
    test01();
    return 0;
}