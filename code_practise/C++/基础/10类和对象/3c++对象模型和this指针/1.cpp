#include<iostream>
using namespace std;
//成员变量与成员函数分开储存
//只有非静态成员变量才属于类的对象
class person{
    
};

class Person{
    public:
        int m_A;
};

class pErson{
    public:
        int m_B;
        static int m_C;
};
int pErson::m_C = 1;

class peRson{
    public:
        int m_D;
        static int m_E;
        void func(){

        }
        static void fuck(){

        }
};

void test01(){
    person p;
    //空对象占用内存空间为：1
    //c++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置
    //每个空对象也应该有一个独一无二的内存地址
    cout<<"sizeof p = "<<sizeof(p)<<endl;
}

void test02(){
    //4
    Person P;
    cout<<"sizeof P = "<<sizeof(P)<<endl;
}

void test03(){
    //4                         静态的不属于类的对象，所以不占类的内存
    pErson Pp;
    cout<<"sizeof Pp = "<<sizeof(Pp)<<endl;
}

void test04(){
    //4                         成员变量与成员函数分开存储
    peRson PP;
    cout<<"sizeof PP = "<<sizeof(PP)<<endl;
}

int main(){
    test01();
    test02();
    test03();
    test04();
    return 0;
}