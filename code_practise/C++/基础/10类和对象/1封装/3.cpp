//struct默认权限为公共
//class默认权限为私有
#include<iostream>
using namespace std;
class C1{
    int m_a;//默认权限私有
};
struct C2{
    int m_B;
};

int main(){
    C1 c1;
    //c1.m_a错误，因为私有 
    C2 c2;
    c2.m_B=100;//正确，公共
    return 0;
}