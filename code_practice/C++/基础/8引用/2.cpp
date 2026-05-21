#include<iostream>
using namespace std;
void myswap1(int a, int b){
    int temp = a;
    a = b;
    b = temp;
    cout<<"myswap1\t"<<a<<"\t"<<b<<endl;
}//值传递

void myswap2(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    cout<<"myswap2\t"<<*a<<"\t"<<*b<<endl;
}//地址传递

void myswap3(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
    cout<<"myswap3\t"<<a<<"\t"<<b<<endl;
}//引用传递`

int main(){
    int a = 10;
    int b = 20;
    cout<<"\t"<<a<<"\t"<<b<<endl;
    myswap1(a,b);
    cout<<"swap1\t"<<a<<"\t"<<b<<endl;
    myswap2(&a,&b);
    cout<<"swap2\t"<<a<<"\t"<<b<<endl;
    myswap3(a,b);//这里的a的类型为&a，是a的别名，b同理
    cout<<"swap3\t"<<a<<"\t"<<b<<endl;    
    return 0;
}
//引用做函数参数
//可以利用引用的技术让形参修饰实参
//可以简化指针修改实参