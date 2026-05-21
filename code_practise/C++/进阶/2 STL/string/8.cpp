#include<iostream>
#include<string>
using namespace std;

//string substr(int pos = 0, int n = npos) const;       返回由pos开始的n个字符组成的字符串

void test01()
{
    string str = "abcdef";
    string subStr = str.substr(1,3);
    cout<<subStr<<endl;
}

void test02()
{
    string email = "hello@sina.com";
    int pos = email.find("@");
    string subStr = email.substr(0,pos);
    cout<<subStr<<pos<<endl;
} 

int main()
{
    test01();
    test02();
    return 0;
}