#include"WorkerManager.h"

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FileName,ios::in);

    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        this->m_EmpNum = 0;
        this->IsFileEmpty = true;
        this->m_EmpArray = NULL;
        ifs.close();
        return;
    }
    //以上为文件不存在
    //一下为文件存在
    char ch;
    ifs >> ch;
    if(ifs.eof())                   //当为空文件时读取的第一个字符为EOF(结尾标志)
    {
        cout<<"文件为空！"<<endl;
        this->m_EmpNum = 0;
        this->IsFileEmpty = true;
        this->m_EmpArray = NULL;
        ifs.close();
        return;
    }

    int num = this->get_EmpNum();
    cout<<"职工人数为："<<num<<endl;
    this->m_EmpNum = num;
} 


void WorkerManager::ShowMenu()
{
    cout<<"~~~~~~~~~~~~~~~~~~~欢迎使用职工管理系统~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~0 退出管理程序：退出当前管理系统~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~1 增加职工信息：批量添加职工功能~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~2 显示职工信息：按照编号显示职工~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~3 删除离职信息：按照编号删除职工~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;   
    cout<<"~~~~~~~~~~~~~4 修改职工信息：按照编号修改职工信息~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~5 查找职工信息：按照职工编号或者职工姓名进行查找相关的人员信息~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~6 按照编号排序：按照职工编号进行排序~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;   
    cout<<"~~~~~~~~~~~~~7 清空所有文档：清空文件中记录的所有职工信息~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;  
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FileName, ios::out);

    for(int i = 0; i<this->m_EmpNum; i++)
    {
        ofs<<this->m_EmpArray[i]->Number<<"\t"<<this->m_EmpArray[i]->Name<<"\t"<<this->m_EmpArray[i]->Department<<endl;
    }
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FileName, ios::in);

    int id;
    string name;
    int department;

    int num = 0;

    while(ifs>>id && ifs>>name && ifs>>department)
    {
        num++;
    }

    ifs.close();

    return num;
}


void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FileName,ios::in);

    int id;
    string name;
    int department;

    int index = 0;
    while(ifs>>id && ifs>>name && ifs>>department)
    {
        Worker *worker = NULL;

        if(department == 1)
        {
            worker = new Employee(id,name,department);
        }
        else if(department == 2)
        {
            worker = new Manager(id,name,department);
        }
        else
        {
            worker = new Boss(id, name, department);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}


int WorkerManager::IsExist(int id)
{
    int index = -1;

    for(int i=0; i<this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->Number == id)
        {
            index = i;
            break;
        }
    }
    return index;
}


void WorkerManager::Find_Emp()
{
    if(this->IsFileEmpty)
    {
        cout<<"文件不存在或记录为空！"<<endl;
    }
    else
    {
        cout<<"请选择查找方式："<<endl;
        cout<<"1 按照职工编号查找。"<<endl;
        cout<<"2 按照职工姓名查找。"<<endl;

        int select = 0;
        cin>>select;

        if(select == 1)
        {
            int number;
            cout<<"请输入要查找的职工编号:"<<endl;
            cin>>number;

            int ret = IsExist(number);
            if(ret != -1)
            {
                cout<<"查找成功！该职工信息如下:"<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout<<"查找失败，该职工编号不存在！"<<endl;
            }
        }
        else if(select == 2)
        {
            string name;
            cout<<"请输入待查找职工姓名："<<endl;
            cin>>name;

            bool flag = false;
            for(int i = 0; i<m_EmpNum; i++)
            {
                if(m_EmpArray[i]->Name == name)
                {
                    cout<<"查找成功！该职工信息如下："<<endl;
                    m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(flag == false)
            {
                cout<<"查找失败！查无此人。"<<endl;
            }
        }
        else
        {
            cout<<"输入有误！"<<endl;
        }
    }

    system("pause");
    system("cls");
}


void WorkerManager::ExitSystem()
{
    cout<<"感谢您的使用，欢迎下次使用。"<<endl;
    system("pause");
    system("cls");
    exit(0);
}



void WorkerManager::AddWorker()
{
    cout<<"请输入增添职工数量："<<endl;
    int num = 0;
    cin>>num;

    if(num>0)
    {
        int newsize = this->m_EmpNum+num;
        Worker **newspace = new Worker*[newsize];
        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i<this->m_EmpNum; i++)
            {
                newspace[i] = this->m_EmpArray[i];
            }
        }
        
        for(int i = 0; i<num; i++)
        {
            string name;
            int department,id;
            cout<<"请输入第"<<i+1<<"个职工的编号："<<endl;
            cin>>id;
            
            cout<<"请输入第"<<i+1<<"个职工的姓名："<<endl;
            cin>>name;

            cout<<"请输入第"<<i+1<<"个职工的岗位编号"<<endl;
            cout<<"1.普通职工 or 2.经理 or 3.老板"<<endl;
            cin>>department;

            int ret = IsExist(id);
            if(ret != -1)
            {
                cout<<"该员工编号已存在，请重新输入："<<endl;
                break;
            }

            Worker *worker = NULL;
            switch(department)
            {
                case 1:
                    worker = new Employee(id,name,1);
                    break;
                case 2:
                    worker = new Manager(id,name,2);
                    break;
                case 3:
                    worker = new Boss(id,name,3);
                    break;
                default:
                    break;
            }
            newspace[this->m_EmpNum+i] = worker;
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = newspace;
        this->m_EmpNum = newsize;
        this->IsFileEmpty = false;
        this->save();
        cout<<"成功添加"<<num<<"名新职工!"<<endl;

    }
    else
    {
        cout<<"输入有误，请重新输入："<<endl;
    }
    system("pause");
    system("cls");
}


void WorkerManager::Show_Emp()
{
    if(this->IsFileEmpty)
    {
        cout<<"文件不存在或记录为空。"<<endl;
    }
    else
    {
        for(int i = 0; i<m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}


void WorkerManager::Delete_Emp()
{
    if(this->IsFileEmpty)
    {
        cout<<"文件不存在或者记录为空！"<<endl;
    }
    else
    {
        cout<<"请输入要删除员工的编号："<<endl;
        int id;
        cin>>id;
        int index = this->IsExist(id);

        if(index != -1)
        {
            for(int i = index; i<this->m_EmpNum; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;
            this->save();
            cout<<"删除成功。"<<endl;
        }
        else
        {
            cout<<"删除失败，此员工不存在。"<<endl;
        }
    }
    system("pause");
    system("cls");
}


void WorkerManager::Mod_Emp()
{
    if(this->IsFileEmpty)
    {
        cout<<"文件不存在或记录为空！"<<endl;
    }
    else
    {
        cout<<"请输入待修改职工的编号："<<endl;
        int id;
        cin>>id;

        int index = this->IsExist(id);
        if(index != -1)
        {
            delete this->m_EmpArray[index];

            int new_id;
            string new_name;
            int new_department;  

            cout<<"查到： "<<id<<"号员工，请输入新职工号："<<endl;
            cin>>new_id;

            cout<<"请输入新职工姓名："<<endl;
            cin>>new_name;

            cout<<"请输入新职工部门："<<endl;
            cout<<"1 普通员工 or 2 经理 or 3 老板 "<<endl;
            cin>>new_department;

            Worker *worker = NULL;
            switch(new_department)
            {
                case 1:
                    worker = new Employee(new_id, new_name,new_department);
                    break;
                case 2:
                    worker = new Manager(new_id, new_name,new_department);
                    break;
                case 3:
                    worker = new Boss(new_id, new_name,new_department);
                    break;
                default:
                    break;
            }

            this->m_EmpArray[index] = worker;

            cout<<"修改成功！"<<endl;

            this->save();
        }
        else
        {
            cout<<"修改失败，查无此人！"<<endl;
        }
    }
    system("pause");
    system("cls");
}


void WorkerManager::sort_Emp()
{
    if(this->IsFileEmpty)
    {
        cout<<"文件不存在或记录为空！"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout<<"请选择排序方式："<<endl;
        cout<<"1 按照职工号进行升序排序。"<<endl;
        cout<<"2 按照职工号进行降序排序。"<<endl;

        int select = 0;
        cin>>select;

        if(select != 1 || select != 2)
        {
            for(int i = 0; i<m_EmpNum;i++)
            {
                int m = i;
                for(int j = i+1; j<m_EmpNum;j++)
                {
                    if(select == 1)
                    {
                        if(m_EmpArray[m]->Number > m_EmpArray[j]->Number)
                        m = j;
                    }
                    else
                    {
                        if(m_EmpArray[j]->Number > m_EmpArray[m]->Number)
                        {
                            m = j;
                        }
                    }
                }
                if(m != i)
                {
                    Worker *temp = m_EmpArray[i];
                    m_EmpArray[i] = m_EmpArray[m];
                    m_EmpArray[m] = temp;
                }
            }
            cout<<"排序成功！"<<endl;
            this->save();
            this->Show_Emp();
        }
    }
}


void WorkerManager::Clean_File()
{
    cout<<"确认清空？"<<endl;
    cout<<"1 确认 or 2 返回"<<endl;

    int select = 0;
    cin>>select;

    if(select == 1)
    {
        ofstream ofs(FileName, ios::trunc);//ios::trunc  如果存在删除文件并重新创建
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for(int i=0; i<this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->IsFileEmpty = true;
        }
        cout<<"清空成功!"<<endl;
    }
    system("pause");
    system("cls");
}


WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray != NULL)
    {
        for(int i=0; i<this->m_EmpNum; i++)
        {
            if(this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
