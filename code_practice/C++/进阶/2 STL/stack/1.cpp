#include<iostream>
#include<stack>

using namespace std;

/*
构造函数：
stack<T> stk;                           stack采用模板类实现，stack对象的默认构造形式
stack(const stack&stk);                 拷贝构造函数

赋值操作：
stack& operator=(const stack &stk);     重载等号操作符

数据存取：
push(elem);                             向栈顶添加元素
pop();                                  从栈顶移除第一个元素
top();                                  返回栈顶元素

大小操作：
empty();                                判断堆栈是否为空
size();                                 返回栈的大小
*/

void test01()
{
    stack<int> stk;

    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    cout<<"栈的大小： "<<stk.size()<<endl;
    while(!stk.empty())
    {
        cout<<"栈顶元素为： "<<stk.top()<<endl;
        stk.pop();
    }
    cout<<"栈的大小： "<<stk.size()<<endl;
}

int main()
{
    test01();
    return 0;
}