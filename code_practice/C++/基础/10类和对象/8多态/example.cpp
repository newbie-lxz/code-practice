#include<iostream>
using namespace std;
class Calculator
{
    public:
        int getResult(char oper)
        {
            if(oper == '+')
            {
                return num1 + num2;
            }
            else if(oper == '-' )
            {
                return num1 - num2;
            }
            else if(oper == '*')
            {
                return num1 * num2;
            }
            else
            {
                return -1;
            }
        }
        //要想拓展新的功能，需要修改源码
        //在真实的开发中，遵循：开闭原则————对扩展进行开发，对修改进行关闭
        int num1;
        int num2;
        char oper;
};

void test01()
{
    Calculator c;
    cin>>c.num1>>c.oper>>c.num2;
    cout<<c.getResult(c.oper)<<endl;
}

int main()
{
    test01();
    return 0;
}