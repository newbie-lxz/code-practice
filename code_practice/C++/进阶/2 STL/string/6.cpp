#include<iostream>
#include<string>
using namespace std;

/*
char& operator[](int n);        通过[]方式取字符
char& at(int n);                通过at方法获取字符
*/

void test01()
{
    string str = "hello";
    cout<<"str = "<<str<<endl;

    for(int i=0; i<str.size(); i++)
    {
        cout<<str[i]<<" ";
    }
    cout<<endl;

    for(int i=0; i<str.size(); i++)
    {
        str.at(i) = 'l';
    }
    cout<<str<<endl;
}

int main()
{
    test01();
    return 0;
}