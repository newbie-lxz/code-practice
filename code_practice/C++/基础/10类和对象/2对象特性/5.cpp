//浅拷贝：编译器提供的拷贝构造函数进行的简单赋值拷贝操作,问题：堆区内存重复释放
//深拷贝：在堆区重新申请一个内存空间进行拷贝操作 
#include<iostream>
using namespace std;
class person{
    public:
        person(){
            cout<<"person的默认构造函数的调用"<<endl;
        }
        person(int age, int height){
            this->age = age;
            this->height = new int(height);
            //堆区空间需要在这个对象销毁前手动释放
            cout<<"person的有参构造函数的调用"<<endl;
        }

        // person(const person &p){
        //     cout<<"拷贝构造函数的调用"<<endl;
        //     age = p.age;
        //     //height = p.height;        编译器默认实现就是这行代码
        //     height = new int(*p.height);
        // }   

        ~person(){
            //析构函数：将堆区开辟的数据做释放操作
            if(height!=NULL){
                delete height;
                height = NULL;//防止野指针出现
            }
            cout<<"person的析构函数的调用"<<endl;
        }
        int age;
        int *height;        //内存开辟到堆区
};
void test01(){
    person p1(18,188);
    cout<<"p1的年龄为:"<<p1.age<<"身高为:"<<*p1.height<<endl;
    person p2(p1);
    cout<<"p2的年龄为:"<<p2.age<<endl;
}
int main(){
    test01();
    return 0;
}//以上是浅拷贝，会出现卡顿然后异常退出，因为重复释放同一内存，应自己实现拷贝构造函数以解决
//未加17-22行的为浅拷贝，有错，加了的转化为深拷贝，无错