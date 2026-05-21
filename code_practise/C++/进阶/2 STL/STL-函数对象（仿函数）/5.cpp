//内建函数对象
//算术仿函数            
//关系仿函数
//逻辑仿函数
#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>

using namespace std;
/*
功能描述：
实现逻辑运算

函数原型：
template<class T> bool logical_and<T>       逻辑与
template<class T> bool logical_or<T>        逻辑或
template<class T> bool logical_not<T>       逻辑非
*/

void test01()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    
    for(vector<bool>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    vector<bool> v2;
    v2.resize(v.size());                //必须有

    transform(v.begin(),v.end(),v2.begin(),logical_not<bool>());        //搬运

    for(vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}