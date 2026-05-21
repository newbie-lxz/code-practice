#include<iostream>
using namespace std;
//递增运算符重载++
class Myinteger
{
    friend ostream &operator<<(ostream &cout, Myinteger myint);
    public:
        Myinteger()
        {
            m_Num = 0;
        }
        //重载前置++
        Myinteger &operator++()
        {
            m_Num++;
            return *this;
        }                                       //返回值的话不能连续，即++(++m_Num)的第二个是对int类型的值的递增，接下来输出m_Num等于1而不等于2
        //重载后置++
        Myinteger operator++(int)              //int代表占位参数，用于区分，只能用int
        {
            Myinteger temp = *this;
            m_Num++;
            return temp;
        }                                       //必须返回值
    private:
        int m_Num;
};

ostream &operator<<(ostream &cout, Myinteger myint)
{
    cout<<myint.m_Num<<endl;
    return cout;
}

void test01()
{
    Myinteger myint;
    cout<<++(++myint);
    cout<<myint;
}

void test02()
{
    Myinteger myint;
    cout<<myint++;                              //(myint++)++没用
    cout<<myint++;
    cout<<myint;
}

int main()
{
    test01();
    test02(); 
    return 0;
}