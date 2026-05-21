#include<iostream>
using namespace std;
//继承
//语法  class 子类 ：继承方式 父类
//子类  也称为  派生类
//父类  也称为  基类
class BasePage                          //公共页面
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
};

class java : public BasePage            //继承BasePage
{
    public:
        void content()
        {
            cout<<"java学科视频"<<endl;
        }
};

class python : public BasePage          //继承BasePage
{
    public:
        void content()
        {
            cout<<"python学科视频"<<endl;
        }
};

class CPP : public BasePage             //继承BasePage
{
    public:
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