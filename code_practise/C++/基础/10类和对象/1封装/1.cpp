#include<iostream>
using namespace std;
#define PI 3.14
//设计一个圆类，求周长
class Circle{
    //访问权限
    //公共权限
    public:
        //属性
        //半径
        int r;
        //行为
        //获取圆的周长
        double C()
        {
            return 2*PI*r;
        }
};

int main(){
    Circle c1;
    c1.r=10;
    cout << "圆的周长为：" << c1.C()<<endl;
    return 0;
}