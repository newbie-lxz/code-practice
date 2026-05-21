#include<iostream>
#include<string>
//用C++风格的字符串
using namespace std;
int main()
{
    char ch='c';
    //单引号
    char str1[] = "hello world";
    //C风格
    string str2 = "hello world";
    //C++风格

    cout<<str1<<"\n"<<str2<<endl;
    cout<<ch<<" "<<(int)ch<<endl;

    bool flag = true;
    cout<<flag<<endl;//1代表真
    flag = false;
    cout<<flag<<endl;//0代表假
    cout<<sizeof(bool)<<endl;//所占内存空间位1个字节
    cin>>flag;
    cout <<flag<<endl;//非0数字都输出1，字母的话不变，前面是1就是1
    system("pause");
    return 0;
}