#include<iostream>
using namespace std;
//对象的初始化和清理

//构造函数(初始化)语法          类名(){}
/*
1 构造函数 没有返回值也不写void
2 函数名称与类名相同
3 构造函数可以有参数，因此可以发生重载
4 程序在调用对象时会自动调用构造，无需手动调用。且只会调用一次
*/
//析构函数(清理)语法          ~类名(){}
/*
1 析构函数 没有返回值也不写void
2 函数名称与类名相同，在名称前加上符号~
3 构造函数不可以有参数，因此不可以发生重载
4 程序在销毁对象前会自动调用析构，无需手动调用。且只会调用一次
*/
class person{
    public:
        person(){
            cout<<"person 构造函数的调用"<<endl;
        }
        ~person(){
            cout<<"person 析构函数的调用"<<endl;
        }
};

void test01(){
    person p;               //在栈上的，test01执行完毕后就会释放这个对象
}
int main(){
    test01();
    person p;               //先有构造
    system("pause");        //然后析构   
    return 0;
}