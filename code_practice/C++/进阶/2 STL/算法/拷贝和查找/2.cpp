#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
replace
功能描述：
将容器内指定范围的旧元素修改为新元素

函数原型：
replace(iterator beg, iterator end, oldvalue, newvalue);
将区间内旧元素替换成新元素
beg 开始迭代器
end 结束迭代器
oldvalue 旧元素
newvalue 新元素
*/

void print(int val)
{
    cout<<val<<" ";
}

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i/2);
    }

    for_each(v.begin(),v.end(),print);
    cout<<endl; 
    
    replace(v.begin(),v.end(),2,0);
    for_each(v.begin(),v.end(),print);
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}