#include<iostream>
#define Pi 3.1415926
using namespace std;
int main()
{
    const float e = 2.71;
    int a=10,b;

    cin>>b;

    cout<<"a="<<a<<" b="<<b<<endl;
    cout<<"Pi="<<Pi<<endl;
    //默认输出6位有效数字
    cout<<"e="<<e<<endl;
    //endl自动换行
    cout<<"int类型所占的内存空间为："<<sizeof(a)<<endl;
    cout<<"float类型所占的内存空间为："<<sizeof(e)<<endl;
    cout<<"Pi所占的内存空间为："<<sizeof(Pi)<<endl;
    system("pause");
    return 0;
}