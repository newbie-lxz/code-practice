//string是一个类， 类内封装了char*， 管理这个字符串， 是一个char*型的容器
#include<iostream>
#include<string>
using namespace std;

/*
string()                        创建一个空的字符串
string(const char* s)           使用字符串s初始化
string(const string& str)       使用一个string对象初始化另一个string对象
string(int n, char c)           使用n个字符c初始化
*/
void test01()
{
    string s1;

    const char* str = "lxz";
    string s2(str);
    cout<<"s2 = "<< s2 << endl;

    string s3(s2);
    cout<<"s3 = "<< s3 << endl;

    string s4(5,'2');
    cout<<"s4 = "<< s4 << endl;
}

int main()
{
    test01();
    return 0;
}