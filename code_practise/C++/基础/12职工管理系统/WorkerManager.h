#pragma once
#include"person.h"
#include<fstream>
#define FileName "empFile.txt"

class WorkerManager
{
    public:
        WorkerManager();
        
        void ShowMenu();            //展现菜单
        void save();                //保存到文件
        int get_EmpNum();           //人数
        void init_Emp();            //初始化数组
        int IsExist(int id);        //员工是否存在
        void Find_Emp();

        void ExitSystem();          
        void AddWorker();
        void Show_Emp();
        void Delete_Emp();
        void Mod_Emp();
        void sort_Emp();
        void Clean_File();

        ~WorkerManager();

        bool IsFileEmpty;       //标志文件是否为空
        int m_EmpNum;           //总人数
        Worker** m_EmpArray;
};