#include<iostream>
using namespace std;
void show(int &c){
    cout<<c<<endl;
    c = 1000; 
}//如果不想修改，在括号里最前面加个const
int main(){
    int a = 10;
    //int &ref = 10;有错,引用必须引一块合法的空间
    const int &ref = 10;//加上const，编译器把代码改为 int temp = 10;constint &ref = temp; 
    //ref = 20; 不可修改

    int b =100;
    show(b);
    cout<<b<<endl;
    return 0;
}
//常量引用使用场景
//用来修饰形参，防止误操作