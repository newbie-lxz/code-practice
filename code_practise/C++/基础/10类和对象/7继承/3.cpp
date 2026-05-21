#include<iostream>
using namespace std;
//继承中的对象模型
//从父类继承过来的成员，全部属于子类对象
class base
{
    public:
        int m_a;
    
    protected:
        int m_b;

    private:
        int m_c;
};

class son1 : public base
{
    public:
        int m_d;
};

void test01()
{
    cout<<"sizeof(son1) = "<<sizeof(son1)<<endl;             //输出16
    //父类中的私有成员属性是被编译器给隐藏了，但依旧被继承了
}

int main()
{
    test01();
    return 0;
}
//p129