#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
swap
功能描述：
互换两个容器的元素

函数原型：
swap(container c1, container c2);
互换两个容器的元素
c1 容器1
c2 容器2
*/

void print(int val)
{
    cout<<val<<"\t";
}

void test01()
{
    vector<int> v1;
    vector<int> v2;

    for(int i=0; i<8; i++)
    {
        v1.push_back(i);
        v2.push_back(i+100);
    }
    swap(v1,v2);
    for_each(v1.begin(),v1.end(),print);
    cout<<endl;
    for_each(v2.begin(),v2.end(),print);
    cout<<endl;
}

int main()
{
    test01();
 
    return 0;
}