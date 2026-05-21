#include<iostream>
using namespace std;
/*
有些类与类之间存在特殊的关系，例如动物中有猫和狗，猫又有许多种，狗也是
定义这些类时下级成员除了拥有上一级的共性，还有自己的特性
这个时候我们可以考虑利用继承的技术，减少重复代码
*/
//普通实现页面
class java
{
    public:
        void header()
        {
            cout<<"首页、公开课、登录、注册……（公共头部）"<<endl;
        }
        void footer()
        {
            cout<<"帮助中心、交流合作、站内地图……（公共底部）"<<endl;
        }
        void left()
        {
            cout<<"java、python、c++(公共分类列表)"<<endl;
        }
        void content()
        {
            cout<<"java学科视频"<<endl;
        }    
};

class python
{
    public:
        void header()
        {
            cout<<"首页、公开课、登录、注册……（公共头部）"<<endl;
        }
        void footer()
        {
            cout<<"帮助中心、交流合作、站内地图……（公共底部）"<<endl;
        }
        void left()
        {
            cout<<"java、python、c++(公共分类列表)"<<endl;
        }
        void content()
        {
            cout<<"python学科视频"<<endl;
        }    
};

class CPP
{
    public:
        void header()
        {
            cout<<"首页、公开课、登录、注册……（公共头部）"<<endl;
        }
        void footer()
        {
            cout<<"帮助中心、交流合作、站内地图……（公共底部）"<<endl;
        }
        void left()
        {
            cout<<"java、python、c++(公共分类列表)"<<endl;
        }
        void content()
        {
            cout<<"c++学科视频"<<endl;
        }    
};

void test01()
{
    java ja;
    cout<<"java下载视频如下"<<endl;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();
    cout<<"---------------------"<<endl;
}

void test02()
{
    python py;
    cout<<"python下载视频如下"<<endl;
    py.header();
    py.footer();
    py.left();
    py.content();
    cout<<"---------------------"<<endl;
}

void test03()
{
    CPP cpp ;
    cout<<"c++下载视频如下"<<endl;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();
    cout<<"---------------------"<<endl;
}

int main()
{
    test01();
    test02();
    test03(); 
    return 0;
}