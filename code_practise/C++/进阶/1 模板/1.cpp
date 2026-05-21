//cpp模板有两种： 函数模板    类模板
/*
函数模板：
制定一个通用函数，返回值类型和形参类型可以不具体制定，而是用虚拟类型来代表
语法：
        template<typename T>        
        函数声明或者定义(这一行写函数，就是函数模板)

template                    声明创建模板
typename                    表示后面是一种数据类型，可以用class代替
T                           通用的数据类型，一般是大写字母，随意设计
*/
#include<iostream>
using namespace std;


template<typename T>
void swapAll(T &a, T &b)    //可以交换任何，比如double，int，char等
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename W>
void putout()
{
    cout<<"no" <<endl;
}

/*
两种方法使用模板
自动类型推导，如test01
显式指定类型，如test02
*/
void test01()
{
    int a = 100;
    int b = 1;
    swapAll(a,b);
    cout<<a<<endl<<b<<endl;
}

void test02()
{
    int a = 100;
    int b = 0;
    swapAll<int>(a,b);      //告诉编译器T是int
    cout<<a<<endl<<b<<endl;
}

//使用模板必须确定W类型
void test03()
{
    //putout();             不可以，因为模板匹配不到相应类型，例如test01是因为a和b类型相同才匹配上的，这个没有参数自然无法匹配
    putout<int>();          //可以，告诉模板W是int
}

int main()
{
    test01();
    test02();
    return 0;
}