#include<iostream>
using namespace std;
void func(int a, int = 10){
    cout << "hello world" << endl;
}//函数占位参数，最后的int = 10 是结合了初始化的知识，可没有赋值只有int
int main(){
    func(10,10);
    //func(10)不行
    return 0;
}