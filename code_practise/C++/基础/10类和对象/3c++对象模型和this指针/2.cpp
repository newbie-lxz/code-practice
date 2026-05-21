#include<iostream>
using namespace std;
//this指针指向被调用的成员函数所属的对象，例如p1调用这个成员函数，this指针就指向p1
//this指针是隐含每一个非静态成员函数内的一种指针，不需要定义

//1 解决名称冲突            当形参和成员变量重名的时候，可以用this指针区分
//2 返回对象本身用*this     在类的非静态成员函数中返回对象本身时，可使用return *this
class person{
    public:
        person(int age){
            this->age = age;
        }

        void personAdd(person &p){
            this->age += p.age;
        }

        person& PersonAdd(person &p){
            this->age += p.age;
            //this 是指向p2的指针,而*this指向的就是p2这个对象的本体
            return *this;
        }

        int age;
};
void test01(){
    person p1(13);
    cout<<"p1的年龄:"<<p1.age<<endl;
}

void test02(){
    person p1(10);
    person p2(10);
    p2.personAdd(p1);
    //不能p2.personAdd(p1).personAdd(p1).personAdd(p1)因为函数返回值时void
    cout<<"p2的年龄:"<<p2.age<<endl;
    p2.PersonAdd(p1).PersonAdd(p1).PersonAdd(p1);
    cout<<"p2的年龄:"<<p2.age<<endl;
}
int  main(){
    test01();
    test02();
    return 0;
}