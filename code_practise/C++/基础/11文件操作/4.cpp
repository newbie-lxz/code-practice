#include<iostream>
#include<fstream>             
using namespace std;
//二进制读文件主要利用流对象调用成员函数read
//函数原型：istream& read(char *buffer, int len);
class person
{
    public:
        char m_name[64];
        int m_age;
};

void test01()
{
    ifstream ifs;
    ifs.open("person.txt", ios::in | ios::binary);
    if(!ifs.is_open())
    {
        return;
    }
    person p;
    ifs.read((char *)&p, sizeof(person));

    cout<<p.m_name<<p.m_age<<endl;
    ifs.close();
}

int main()
{
    test01();
    return 0;
}