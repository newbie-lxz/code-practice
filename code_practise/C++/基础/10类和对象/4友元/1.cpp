#include<iostream>
#include<string>
using namespace std;
class building
{
    friend void goodgay(building *building);            
    //全局函数做友元，把函数声明放入类的最前面再加上friend关键字，可以访问private成员
    public:
        building()
        {
            m_sittingroom = "客厅";
            m_bedroom = "卧室";
        }
        string m_sittingroom;
    private:
        string m_bedroom;
};

void goodgay(building *building)                    
{
    cout<<"好基友全局函数 正在访问 :"<<building->m_sittingroom<<endl;
    cout<<"好基友全局函数 正在访问 :"<<building->m_bedroom<<endl;
}

void test01()
{
    building building;
    goodgay(&building);
}


int main(){
    test01();
    return 0;
}