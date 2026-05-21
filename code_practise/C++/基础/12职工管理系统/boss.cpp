#include"boss.h"

Boss::Boss(int number, string name, int department)
{
    this->Number = number;
    this->Name = name;
    this->Department = department;
}

void Boss::showInfo()
{
    cout<<"职工编号： "<< this->Number;
    cout<<"\t职工姓名: "<<this->Name;
    cout<<"\t岗位: "<<this->GetDepartment();
    cout<<"\t岗位职责: 管理公司所有业务"<<endl;

}

string Boss::GetDepartment()
{
    return string("老板");
}