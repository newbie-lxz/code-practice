#include<iostream>
using namespace std;
//多态好处：
//1、结构清晰
//2、可读性强
//3、后期拓展和维护方便
class AbstractCalculator
{
    public:
        virtual int GetResult()
        {
            return 0;
        }
        int m_num1;
        int m_num2;

};

class AddCalculator : public AbstractCalculator
{
    public:
        int GetResult()
        {
            return m_num1 + m_num2;
        }
};

class MinusCalculator : public AbstractCalculator
{
    public:
        int GetResult()
        {
            return m_num1 - m_num2;
        }
};

class MultiplyCalculator : public AbstractCalculator
{
    public:
        int GetResult()
        {
            return m_num1 * m_num2;
        }
};

void test01()
{
    AbstractCalculator *abc = new AddCalculator;                    //父类用指针指向子类对象
    abc->m_num1 = 10;
    abc->m_num2 = 20;
    cout<<abc->GetResult()<<endl;
    delete abc;
    abc = NULL;
}

int main()
{
    test01();
    return 0;
}