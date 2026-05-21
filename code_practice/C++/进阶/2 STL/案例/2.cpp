#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<ctime>

#define CEHUA 1
#define MEISHU 2
#define YANFA 3

using namespace std;

class Worker
{
    public:
        string m_name;
        int m_salary;
};

void createWorker(vector<Worker> &w)
{
    string name = "ABCDEFGHIJ";
    for(int i=0; i<10; i++)
    {
        Worker worker;
        worker.m_name = "员工";
        worker.m_name += name[i];
        worker.m_salary = rand()%5000 + 10000;
        w.push_back(worker);
    }
}

void assignDepartment(multimap<int,Worker>&mmp, vector<Worker> &w)
{
    for(int i=0; i<10; i++)
    {
        int department = rand()%3+1;
        mmp.insert(pair<int,Worker>(department,w[i]));
    }
}

void print(multimap<int,Worker> mmp)
{
    cout<<"策划部门："<<endl;
    multimap<int,Worker>::iterator pos = mmp.find(CEHUA);
    for(;pos!=mmp.find(MEISHU);pos++)
    {
        cout<<"姓名: "<<pos->second.m_name<<"\t工资: "<<pos->second.m_salary<<endl;
    }

    cout<<"美术部门："<<endl;
    for(;pos!=mmp.find(YANFA);pos++)
    {
        cout<<"姓名: "<<pos->second.m_name<<"\t工资: "<<pos->second.m_salary<<endl;
    }

    cout<<"研发部门："<<endl;
    for(;pos!=mmp.end();pos++)
    {
        cout<<"姓名: "<<pos->second.m_name<<"\t工资: "<<pos->second.m_salary<<endl;
    }
}

int main()
{
    srand(time(0));
    vector<Worker> worker;
    createWorker(worker);
    multimap<int, Worker> mmp;
    assignDepartment(mmp,worker);
    print(mmp);
    return 0;
}