//类模板分文件编写
/*
问题：
    类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到
解决：
    1 直接包含.cpp源文件
    2 将声明和实现写在同一个文件中，并更改后缀名为.hpp, .hpp是约定的名称，并不是强制
*/

#include"Person.cpp"

void test()
{
    Person<string,int> p("lxz",19);
    p.showPerson();
}

int main()
{
    test();
    return 0;
}