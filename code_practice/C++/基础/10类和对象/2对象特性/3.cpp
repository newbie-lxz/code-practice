//拷贝构造函数调用时机 
/*
1 使用一个已经创建完毕的对象初始化另一个新对象
2 值传递的方式给函数参数传值
3 值方式返回局部对象
*/
#include<iostream>
using namespace std;
class person{
    public:
        person(){
            cout<<"person默认构造函数调用"<<endl;
        }
        person(int age){
            cout<<"person有参构造函数调用"<<endl;
            this->age = age;
        }
        person(const person &p){
            cout<<"person拷贝构造函数调用"<<endl;
            age = p.age;
        }

        ~person(){
            cout<<"person析构函数调用"<<endl;
        }
        int age;
};
//1 使用一个已经创建完毕的对象初始化另一个新对象
void test01(){
    person p1(20);
    person p2(p1);
    cout<<"p2的年龄:"<<p2.age<<endl;
}
//2 值传递的方式给函数参数传值
void dowork(person p){
    //把test02里的实参p传给这里的形参p，接下来相当于拷贝，在这个函数里生成一个新的对象，同时在这里接下来改动p.age不影响test02里的p的数据
}
void test02(){
    person p;
    dowork(p);
}
//3 值方式返回局部对象
person dowork2(){
    person p1;
    cout<<(int*)&p1<<endl;
    return p1;//返回时这个p1已经没了，返回的是一个新的对象
}
void test03(){
    person p = dowork2();
    cout<<(int*)&p<<endl;
}
int main(){
    test01();
    test02();
    test03();
    return 0;
}