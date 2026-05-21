#include<iostream>
#include<fstream>               //对文件操作
using namespace std;
//文件类型：文本文件(以文本的ASCII码存储)or二进制文件(以文件二进制形式存储)
/*
操作文件三大类：
1 ofstream 写操作
2 ifstream 读操作
3 fstream  读写操作
*/

//文本文件————写文件
/*
1 包含头文件 <ofstream>
2 创建流对象 ofstream ofs;
3 打开文件   ofs.open("文件路径",打开方式);
4 写数据     ofs<<"写入的数据"
5 关闭文件   ofs.close();
*/
/*
文件打开方式：
ios::in         为读文件而打开文件
ios::out        为写文件而打开文件
ios::ate        初始位置：文件尾
ios::app        追加方式写文件
ios::trunc      如果文件存在先删除，再创建
ios::binary     二进制方式

文件打开方式可以配合使用，利用|操作符
例如：用二进制方式写文件  ios::binary | ios::out
*/

void test01()
{
    ofstream ofs;
    ofs.open("test1.txt",ios::out);             //默认创建位置是该项目所在路径
    ofs<<" i love gxy "<<endl;
    ofs<<" i am lxz "<<endl;
    ofs.close();
}

int main()
{
    test01();
    return 0;
}