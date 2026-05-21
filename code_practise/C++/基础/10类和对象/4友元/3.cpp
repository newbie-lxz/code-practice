#include<iostream>
#include<string>
using namespace std;
//成员函数做友元
class Building;
class Goodgay
{
    public:
        Goodgay();
        void visit();                //让visit函数可以访问Building的私有成员
        void visit2();               //让visit2函数不可以访问Building的私有成员
        Building *building;
};
class Building
{
    friend void Goodgay::visit();   //Goodgay类下的visit成员函数作为本类的好朋友，可以访问
    public:
        Building();
        string m_sittingroom;
    private:
        string m_bedroom;
};
Building::Building()  
{ 
    m_sittingroom = "客厅";
    m_bedroom = "卧室";
} 

Goodgay::Goodgay()
{
    //创建一个建筑物对象
    building = new Building;
}
void Goodgay::visit()
{
    cout<<"visit函数正在访问: "<<building->m_sittingroom<<endl;
    cout<<"visit函数正在访问: "<<building->m_bedroom<<endl;
}
void Goodgay::visit2()
{
    cout<<"visit2函数正在访问: "<<building->m_sittingroom<<endl;
    //cout<<"visit2函数正在访问: "<<building->m_bedroom<<endl;
}

void test01()
{
    Goodgay gg;
    gg.visit();
    gg.visit2();
}

int main(){
    test01();
    return 0;
}