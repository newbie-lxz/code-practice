#include<iostream>
#include<fstream>             
using namespace std;

//二进制写文件主要利用流对象调用成员函数
//ostream& write(const char* buffer, int len);
//参数解释：字符指针buffer指向内存中的一段存储空间，len是读写的字节数

class person
{
    public:
        char m_name[64];
        int m_age;
};
//二进制文件————写文件
/*
1 包含头文件 <ofstream>
2 创建流对象 ofstream ofs;
3 打开文件   ofs.open("文件路径",打开方式);
4 写数据     ofs<<"写入的数据"
5 关闭文件   ofs.close();
*/
void test01()
{
    person p = {"李熙正", 19};
    ofstream ofs;
    ofs.open("person.txt", ios::out | ios::binary);
    if (ofs.is_open()) {
        ofs.write((const char*)&p, sizeof(person));
        ofs.close();
        cout << "文件写入成功！" << endl;
    } else {
        cout << "文件打开失败！" << endl;
    }
}

int main()
{
    test01();
    return 0;
}