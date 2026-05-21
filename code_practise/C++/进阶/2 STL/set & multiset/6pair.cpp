#include<iostream>
#include<string>
using namespace std;

/*
对组
pair<type,type> p (value, value2);
pair<type,type> p = make_pair(value1, value2);
tuple<int,int,int> t(1,1,1);
*/

void test01()
{
    pair<string, int> p("lxz",20);
    cout<<"name: "<<p.first<<"age: "<<p.second<<endl;

    pair<string, int> p2 = make_pair("gxy", 19);
    cout<<"name: "<<p2.first<<"age: "<<p2.second<<endl;    
}

int main()
{
    test01();
    return 0;
}