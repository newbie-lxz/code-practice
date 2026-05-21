#include"employee.h"

Employee::Employee(int number, string name, int department)
{
    this->Number = number;
    this->Name = name;
    this->Department = department;
}

void Employee::showInfo()
{
    cout<<"职工编号： "<< this->Number;
    cout<<"\t职工姓名: "<<this->Name;
    cout<<"\t岗位: "<<this->GetDepartment();
    cout<<"\t岗位职责: 完成经理交给的任务"<<endl;
}

string Employee::GetDepartment()
{
    return string("员工");
}