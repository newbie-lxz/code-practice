#include<iostream>
using namespace std;
//递减运算符重载
class decrease
{
    friend ostream &operator<<(ostream &cout, decrease p);
    public:
        decrease()
        {
            m_a = 1;
            m_b = 3;
        }
        decrease &operator--()
        {
            m_a--;
            m_b--;
            return *this;
        }
        decrease operator--(int)
        {
            decrease temp = *this;
            m_a--;
            m_b--;
            return temp;
        }
    private:
        int m_a;
        int m_b;
};

ostream &operator<<(ostream &cout, decrease p)
{
    cout<<"m_a = "<<p.m_a<<endl;
    cout<<"m_b = "<<p.m_b<<endl;
    return cout;
}

void test01(){
    decrease p;
    cout<<"--(--p) = "<<endl<<--(--p);
}

void test02(){
    decrease p;
    cout<<"(p--)-- = "<<endl<<(p--)--;
}

int main()
{
    test01();
    test02();
    return 0;
}