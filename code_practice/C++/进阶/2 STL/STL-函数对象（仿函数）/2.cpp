/*
返回bool类型的仿函数成为   谓词
如果operator()接受一个参数，那么叫做一元谓词
如果operator()接受两个参数，那么叫做二元谓词
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Greater5
{
    public:
        bool operator()(int val)
        {
            return val > 5;
        }
};

class myCompare
{
    public:
        bool operator()(int v1, int v2)
        {
            return v1>v2;
        }
};

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }
    //Greater5() 匿名函数对象
    vector<int>::iterator pos = find_if(v.begin(),v.end(),Greater5());          //返回迭代器
    if(pos==v.end())
    {
        cout<<"not find"<<endl;
    }
    else
    {
        cout<<"find it\t"<<*pos<<endl;
    }
}
 
void test02()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(40);
    v.push_back(30);
    v.push_back(50);

    sort(v.begin(),v.end());
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    sort(v.begin(),v.end(),myCompare());
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}