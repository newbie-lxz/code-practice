#include<iostream>
using namespace std;
//const修饰成员函数

class person{
    public:
/*
常函数
成员函数后加const后我们称这个函数为常函数
常函数内不可修改成员属性
成员属性声明时加关键字mutable后，在常函数中依然可以修改
*/
    //17行相当于this->m_A=100，this指针的本质为指针常量，指针的指向不可以修改,结合18和29行理解，即person *const this
        void showperson()   const
        {
            m_B = 100;          //不报错
            //m_A = 100;        报错，加了const就不允许修改了,相当于const person *const this的const
            //this=NULL;        报错，this指针为指针常量,已经指向对象了，不可修改指向
        }

        void func(){}

        int m_A;
        mutable int m_B;                //特殊变量，即使在常函数中，也可以修改这个值,加关键字mutable
};

void test01(){
    person p;
    p.showperson();         //调用这个成员函数时this指针指向这个p
}

void test02(){
/*
常对象
声明对象前加const称该对象为常对象
常对象只能调用常函数
*/
    person P;
    const person p = P;     //常对象,要初始化
    //p.m_A = 100;         不可修改
    p.m_B = 1000;           //不报错，m_B特殊
    p.showperson();
    //p.func();             报错，常对象只能调用常函数，不能调用普通成员函数，因为普通成员函数可以修改属性
}

int main(){
    return 0;
}