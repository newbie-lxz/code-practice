#pragma once
#include"worker.h"

class Manager : public Worker
{
    public:
        Manager(int number, string name, int department);

        virtual void showInfo();
        virtual string GetDepartment();
};