//初始化列表
//构造函数()：属性1(值1)，属性2(值2)···{}
#include<iostream>
using namespace std;
class person{
    public:
        //传统初始化操作
        // person(int a, int b, int c){
        //     A = a;
        //     B = b;
        //     C = c;
        // }

        // person():A(100),B(200),C(300){
        // }太死板，只能是100，200，300

        person(int a,int b, int c):A(a),B(b),C(c){

        }

        int A;
        int B;
        int C;
};
// void test01(){
//     person p1(10,20,30);
//     cout<<"A = "<<p1.A<<endl;
//     cout<<"B = "<<p1.B<<endl;
//     cout<<"C = "<<p1.C<<endl;   
// }

void test02(){
    person p2(30,20,10);
    cout<<"A = "<<p2.A<<endl;
    cout<<"B = "<<p2.B<<endl;
    cout<<"C = "<<p2.C<<endl;   
}
int main(){
    //test01();
    test02();
    return 0;
}