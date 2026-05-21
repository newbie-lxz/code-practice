#include"manager.h"

Manager::Manager(int number, string name, int department)
{
    this->Number = number;
    this->Name = name;
    this->Department = department;
}

void Manager::showInfo()
{
    cout<<"职工编号： "<< this->Number;
    cout<<"\t职工姓名: "<<this->Name;
    cout<<"\t岗位: "<<this->GetDepartment();
    cout<<"\t岗位职责: 完成老板交给的任务，并下发给员工"<<endl;
}

string Manager::GetDepartment()
{
    return string("经理");
}