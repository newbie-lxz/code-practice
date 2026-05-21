#pragma once
#include"worker.h"

class Boss : public Worker
{
    public:
        Boss(int number, string name, int department);

        void showInfo();
        string GetDepartment();
};