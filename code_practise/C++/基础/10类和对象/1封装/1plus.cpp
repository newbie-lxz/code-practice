#include<iostream>
#include<string>
using namespace std;
class student{
    public:
        string name;
        string ID;
        void show(){
            cout<<"name:"<<name<<endl;
            cout<<"ID:"<<ID<<endl;
        }
        void set(string name,string ID){
            this->name = name;//this所指的为成员变量
            this->ID = ID;
        }
};
int main(){
    student s1;
    cin>>s1.name;
    cin>>s1.ID;
    s1.set(s1.name,s1.ID);
    s1.show();
    return 0;
}