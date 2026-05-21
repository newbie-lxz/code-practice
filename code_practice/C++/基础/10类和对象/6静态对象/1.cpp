#include<iostream>
using namespace std;
/*
静态成员变量：
    所有对象共享同一份数据
        可以通过对象进行访问，也可以通过类名进行访问
    在编译阶段分配内存
    类内声明，类外初始化
*/
class person
{
    public:
        static int m_A;             //类内声明
        int m_C;
        static void func(){
            m_A = 1000;             //静态成员函数可以访问静态成员变量
            //m_C = 0;              //非静态成员变量，报错
            cout<<"static void func调用"<<endl;
        }
    
    private:
        static int m_B;

};

int person::m_A = 100;              //类外初始化,person作用域下的
//int person::m_B = 200;            只有public才可以，其他的没有权限

/*
静态成员函数：
    所有对象共享同一个函数
    静态成员函数只能访问静态成员变量
        因为函数共享，访问时不知道访问的是哪一个对象的非静态成员变量，而静态成员变量也是共享的不需要区分
*/

void test01(){
    person p;
    cout<<p.m_A<<endl;
    person p2;
    p2.m_A = 200;
    cout<<p.m_A<<endl;              //p,p2共享这一个数据
}

void test02(){
    //通过对象进行访问
    person p;
    cout<<p.m_A<<endl;
    //通过类名进行访问
    cout<<person::m_A<<endl;
}

void test03(){
    //通过对象访问
    person p;
    p.func();

    //通过类名访问
    person::func();
}

int main(){
    //test01();
    //test02();
    test03();
    return 0;
}