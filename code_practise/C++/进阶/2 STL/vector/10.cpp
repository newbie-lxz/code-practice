#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

//reserve(int len)      容器预留len个元素长度，预留位置不初始化，元素不可访问

void printVector(vector<int> &v)
{
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void test01()
{
    vector<int> v;

    int num = 0;
    int *p = NULL;
    for(int i=0; i<100000; i++)
    {
        v.push_back(i);
        if(p != &v[0])
        {
            p = &v[0];
            num++;
        }
    }
    cout<<"num = "<<num<<endl;
}

void test02()
{
    vector<int> v;
    v.reserve(100000);
    
    int num = 0;
    int *p = NULL;
    for(int i=0; i<100000; i++)
    {
        v.push_back(i);
        if(p != &v[0])
        {
            p = &v[0];
            num++;
        }
    }
    cout<<"num = "<<num<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}