#include<iostream>
#include<string>
using namespace std;
//类做友元
class Building
{
    friend class Goodgay;           //Goodgay类是本类的好朋友，可以访问私密信息,class可以省略
    public:
        Building();
        string m_sittingroom;
    private:
        string m_bedroom;
};
//类外写成员函数
Building::Building()
{ 
    m_sittingroom = "客厅";
    m_bedroom = "卧室";
} 


class Goodgay
{
    public:
        Goodgay();
        void visit();               //参观函数，访问building中的属性

        Building *building;
};
Goodgay::Goodgay()
{
    //创建一个建筑物对象
    building = new Building;
}
void Goodgay::visit()
{
    cout<<"好基友类正在访问："<<building->m_sittingroom<<endl;
    cout<<"好基友类正在访问："<<building->m_bedroom<<endl;
}

void test01(){
    Goodgay gg;
    gg.visit();
}

int main()
{
    test01();
    return 0;
}