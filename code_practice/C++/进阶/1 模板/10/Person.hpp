#pragma once
#include<iostream>
#include<string>
using namespace std;

class Person
{
    public:
        Person(){};
        Person(string name, int age)
        {
            this->m_Age = age;
            this->m_Name = name;
        }

        string m_Name;
        int m_Age;
};