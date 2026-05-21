//构造函数的分类及调用
/*      分类
1 有参构造和无参构造
2 普通构造和拷贝构造
*/
/*      调用
1 括号法
2 显示法
3 隐式转换法
*/
#include<iostream>
using namespace std;

class person
{
    public:
        person()
        {
            cout<<"person 的无参(默认)构造函数的调用"<<endl;
        }
        person(int a)
        {
            age = a;
            cout<<"person 的有参构造函数的调用"<<endl;
        }
        person(const person &p)     //一定要加const，而且有以引用的的方式传进来，把p这个人的数据拷贝下来同时不改变p
        {
            age = p.age;
            cout<<"person 的拷贝构造函数的调用"<<endl;
        }

        ~person()
        {
            cout<<"person 的析构函数的调用"<<endl;
        }
        int age;
};
void test01(){
    //1 括号法
    person p1;           //无参(默认)构造函数的调用
    person p2(10);       //有参构造函数的调用
    person p3(p2);       //拷贝构造函数的调用
    cout<<"p2的年龄:"<<p2.age<<endl;
    cout<<"p3的年龄:"<<p3.age<<endl;
    //调用无参(默认)构造函数时不加()
    //若是person p1();  会被编译器当成是一个函数的声明
    
    //2 显示法
    person pp1 = person(10);    //有参构造函数的调用
    person pp2 = person(pp1);   //拷贝构造函数的调用
    //person(10);                 匿名对象 当前行执行结束后，系统会立即回收掉匿名对象
    //不要利用拷贝构造函数 初始化匿名对象   就是不能单独写person(pp1), 编译器会认为这个等价于person pp1,相当于实例化一个无参构造，而前面已经定义过pp1，会发生重定义

    //3 随式转换法
    person pp3 = 10;            //相当于写了person pp3 = person(10)
    person pp4 = pp3;           //拷贝构造

}
int main(){
    test01();
    return 0;
}