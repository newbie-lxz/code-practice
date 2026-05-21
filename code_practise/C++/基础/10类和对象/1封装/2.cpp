#include<iostream>
using namespace std;
//访问权限3种
//public 公共权限 成员 类内可以访问，类外也可以访问
//protected 保护权限 成员 类内可以访问，类外不可以访问 儿子可以访问父亲中的保护内容
//private 私有权限 成员 类内可以访问，类外不可以访问 儿子不能访问父亲中的私有内容
class Person{
    public:
        string name;
    protected:
        string car;
    private:
        string password;

    public:
        void func(){
            name = "lxz";
            car = "bench";
            password = "114514";
        }
};
int main(){
    Person p1;
    p1.name="gxy";
    p1.func(); 
    //没有p1.car和p1.password。类外访问不到
    return 0;
}