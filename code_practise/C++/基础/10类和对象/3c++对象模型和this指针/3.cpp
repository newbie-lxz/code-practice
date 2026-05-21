#include<iostream>
using namespace std;
//空指针访问成员函数
//c++中空指针也是可以调用成员函数的，但是要注意有没有用到this指针，如果用到this指针，需要加以判断保证代码的健壮性
class person{
    public:
        void showclassname(){
            cout<<"this is person class"<<endl;
        }

        void showpersonage(){
            //报错原因是因为传入的指针是NULL，this是空的怎么能访问里面的属性呢
            if(this==NULL){
                return;
            }//增加13-15行增加代码的健壮性
            cout<<"age = "<<this->m_age<<endl;
        }

        int m_age;
};

void test01(){
    person *p = NULL;
    p->showclassname();
    p->showpersonage();
    //空指针可以访问成员函数，只不过没东西
}

int main(){
    test01();
    return 0;
}