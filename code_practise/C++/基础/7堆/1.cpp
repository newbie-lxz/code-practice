#include<iostream>
using namespace std;
int *NEW1(){
    int *p = new int(10);   //在堆区分配内存，初始化为10
    return p;
}
int *NEW2(){
    int *arr = new int[10]; //十代表数组有十个元素
    return arr;
}
void test(int *p,int *arr){
    cout<<*p<<endl;
    delete p;               //释放内存
    cout<<*p<<endl;
    for(int i=0;i<10;i++){
        arr[i]=i+100;
        cout<<arr[i]<<endl;
    }
    delete[] arr;          //释放数组要加个中括号说明释放的是一个数组； 

}
int main(){
    test(NEW1(),NEW2());
    return 0;
}