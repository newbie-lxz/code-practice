#include<iostream>
#include<fstream>             
using namespace std;
#include<string>
//读文件
/*
1 包含头文件        <ofstream>
2 创建流对象        ifstream ifs;
3 打开文件并判断    ifs.open("文件路径",打开方式);
4 四种方式读取
5 关闭文件          ifs.close();
*/
void test01()
{
    ifstream ifs;
    ifs.open("test1.txt",ios::in);
    if(!ifs.is_open())          //返回一个bool类型的
    {
        cout<<"文件打开失败。"<<endl;
        return;
    }
    //第一种
    // char buf[1024] = {0};
    // while(ifs>>buf)             //遇到空格或者回车停止
    // {
    //     cout<<buf<<endl;
    // }
    
    //第二种
    // char buf[1024] = {0};
    // while(ifs.getline(buf,sizeof(buf)))            //读取一行的数据
    // {
    //     cout<<buf<<endl;
    // }

    //第三种
    // string buf;
    // while(getline(ifs,buf))
    // {
    //     cout<<buf<<endl;
    // }
    
    //第四种
    char c;
    while((c = ifs.get()) != EOF)                    //end of file
    {
        cout<<c;
    }

    ifs.close();
}

/*
读数据：
1   22~27
2   29~34
3   36~41
4   43~48(不推荐)
*/

int main()
{
    test01();
    return 0;
}