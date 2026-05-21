#pragma once
#include<iostream>
#include<string>

using namespace std;

class Worker
{
    public:
        virtual void showInfo() = 0;
        virtual string GetDepartment() = 0;

        int Number;
        string Name;
        int Department;
};