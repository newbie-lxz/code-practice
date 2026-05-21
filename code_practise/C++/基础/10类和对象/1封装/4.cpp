//企业开发一般都是私有，仅自己控制读写权限
#include<iostream>
#include<string>
using namespace std;
//私有权限
//可以自己控制读写权限
//对于写可以检测数据的有效性
class Person{
    public:
        void setname(string name){
            this->name=name;
        }//设置姓名

        string getname(){
            return name;
        }//获取姓名

        int getage(){
            return age;
        }

        void setidol(string idol){
            this->idol = idol;
        }

    private:
        string name;        //可读可写
        
        int age = 18;       //只读
        
        string idol;        //只写  
};
int main(){
    Person p1;
    p1.setname("孔德舟");
    cout << "姓名：" << p1.getname() << endl;
    cout << "年龄:"  << p1.getage() << endl;    //没有setage不能写
    p1.setidol("小明");                         //没有getidol不能读
    return 0;
}