#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

//vector容器互换

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
    vector<int> v1;
    for(int i=0; i<10; i++)
    {
        v1.push_back(i);
    }
    cout<<"交换前： "<<endl;
    printVector(v1);

    vector<int> v2;
    for(int i=10; i>0; i--)
    {
        v2.push_back(i);
    }
    printVector(v2);

    cout<<"交换后： "<<endl;
    v1.swap(v2);
    printVector(v1);
    printVector(v2);
}

//实际用途： 巧用swap可以收缩内存空间
void test02()
{
    vector<int> v;
    for(int i=0; i<100000; i++)
    {
        v.push_back(i);
    }
    cout<<"v 的容量： "<<v.capacity()<<endl;
    cout<<"v 的大小： "<<v.size()<<endl;

    v.resize(3);
    cout<<"v 的容量： "<<v.capacity()<<endl;
    cout<<"v 的大小： "<<v.size()<<endl;
    //太浪费空间
    vector<int>(v).swap(v);         //收缩内存
    cout<<"v 的容量： "<<v.capacity()<<endl;
    cout<<"v 的大小： "<<v.size()<<endl;
}

int main()
{
    test01();
    test02();
    return 0;
}