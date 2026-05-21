#pragma once
#include"worker.h"

class Employee : public Worker
{
    public:
        Employee(int number, string name, int department);

        void showInfo();
        string GetDepartment();
};