#include"WorkerManager.h"
/*
0 退出管理程序：退出当前管理系统
1 增加职工信息：实现批量添加职工功能，将信息录入到文件中，职工信息为：职工编号、姓名、部门编号
2 显示职工信息：显示公司内部所有职工的信息
3 删除离职信息：按照编号删除指定职工
4 修改职工信息：按照编号修改职工个人信息
5 查找职工信息：按照职工编号或者职工姓名进行查找相关的人员信息
6 按照编号排序：按照职工编号进行排序，排序规则由用户指定
7 清空所有文档：清空文件中记录的所有职工信息(清空前需要再次确认，防止误删)
*/
int main()
{
    WorkerManager wm;
    char choice = '0';
    while(true)
    {
        wm.ShowMenu();
        cout<<"请输入您的操作: ";
        cin>>choice;
        switch(choice)
        {
            case '0':
                wm.ExitSystem();
            case '1':
                wm.AddWorker();
                break;
            case '2':
                wm.Show_Emp();
                break;
            case '3':
                wm.Delete_Emp();
                break;
            case '4':
                wm.Mod_Emp();
                break;
            case '5':
                wm.Find_Emp();
                break;
            case '6':
                wm.sort_Emp();
                break;
            case '7':
                wm.Clean_File();
                break;
            default:
                cout<<"输入无效，请重新输入。"<<endl;
                system("pause");
                system("cls");
        }
    }
} 