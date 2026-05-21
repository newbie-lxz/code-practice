//类对象作为类成员
#include<iostream>
#include<string>
using namespace std;
class phone{
    public:
        phone(string pho_name){
            this->pho_name = pho_name;
            cout<<"phone的构造函数调用"<<endl;
        }
        ~phone(){
            cout<<"phone的析构函数的调用"<<endl;
        }
        string pho_name;
};

class person{
    public:
        //phone pho = name2    隐式转换法
        person(string name1,string name2):per_name(name1),pho(name2){
            cout<<"person的构造函数调用"<<endl;
        }
        ~person(){
            cout<<"person的析构函数的调用"<<endl;
        }
        string per_name;
        phone pho; 
};

void test01(){
    person p("张三","xiaomi");
    cout<<p.per_name<<"拿着"<<p.pho.pho_name<<endl;
}
//当其他类对象作为本类成员，构造时候先构造类对象，在构造自身
int main(){
    test01();
    return 0;
}