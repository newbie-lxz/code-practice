#pragma once
#include<iostream>
#include"practice2plus_point.h"
using namespace std;
class circle{
    public:
        void setR(int r);
        int getR();
        void setO(point center);
        point getO();

    private:
        int r;
        point O;
};