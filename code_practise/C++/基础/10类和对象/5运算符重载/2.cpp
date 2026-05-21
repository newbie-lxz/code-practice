#include<iostream>
using namespace std;
//左移运算符<< 重载
//不能利用成员函数重载左移运算符，因为无法实现cout在左侧
class person
{
    friend ostream &operator<<(ostream &cout, person p);
    public:
        person(int c=10)
        {
            m_C = c; 
        }
    public:
        int m_A;
        int m_B;
    private:
        int m_C;
    //作为友元才能有机会访问私有权限的成员  
};

ostream &operator<<(ostream &cout, person p)//本质operator<<(cout,p) 简化cout << p
{
    cout<<"m_A = "<<p.m_A<<endl;
    cout<<"m_B = "<<p.m_B<<endl;
    cout<<"m_C = "<<p.m_C<<endl;
    return cout;
}

void test01()
{
    person p;
    p.m_A = 10;
    p.m_B = 20;
    cout<<p<<endl;                        
}
//如果21行是void operator<<(ostream &cout, person &p),没有26行，那么34行就不能有endl等多余的，即好几个对象

int main()
{
    test01(); 
    return 0;
}