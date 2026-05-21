// 添加联系人：向通讯录中添加新人，信息包括（姓名、性别、年龄、联系电话、家庭住址）最多记录1000人
// 显示联系人：显示通讯录中所有联系人信息
// 删除联系人：按照姓名进行删除指定联系人
// 查找联系人：按照姓名查看指定联系人信息
// 修改联系人：按照姓名重新修改指定联系人
// 清空联系人：清空通讯录中所有信息
// 退出通讯录：退出当前使用的通讯录
#include<iostream>
#include<string>
using namespace std;
#define MAX 1000
struct contacts 
{
    int flag=0;
    //在C++中，contacts() : flag(0) {} 是一个构造函数的定义，用于初始化 contacts 结构体中的 flag 成员变量为0。这是C++类和结构体初始化的一种常用方式，称为成员初始化列表。
    string name;
    int gender;
    int age;
    string number;
    string home;
};

void Menu();
void Addcontacts(struct contacts num[]);
void Showcontacts(struct contacts num[]);
void Deletecontacts(struct contacts num[]);
void Findcontacts(struct contacts num[]);
void Changecontacts(struct contacts num[]);
void empty(struct contacts num[]);

int main(){
    contacts Address[MAX];
    int command;
    do{
        Menu();
        cin >> command;
        switch(command){
            case 1:
                Addcontacts(Address);
                break;
            case 2:
                Showcontacts(Address);
                break;
            case 3:
                Deletecontacts(Address);
                break;
            case 4:
                Findcontacts(Address);
                break;
            case 5:
                Changecontacts(Address);
                break;
            case 6:
                empty(Address);
                break;
            default:
                break;
        }
    }while(command!=7);
    cout << "欢迎下次使用。" <<endl;
    system("pause");
    return 0;
}

void Menu(){
    cout << "使用说明：" << endl;
    cout << "1: 添加联系人 " << endl;
    cout << "2: 显示联系人 " << endl;
    cout << "3: 删除联系人(按照姓名) " << endl;
    cout << "4: 查找联系人(按照姓名) " << endl;
    cout << "5: 修改联系人(按照姓名) " << endl;
    cout << "6: 清空联系人 " << endl;
    cout << "7: 退出通讯录 " << endl;
}
// 添加联系人：向通讯录中添加新人，信息包括（姓名、性别、年龄、联系电话、家庭住址）最多记录1000人
void Addcontacts(struct contacts num[]){
    cout<<"添加新联系人："<<endl;
    for(int i=0; i<MAX; i++){
        if(num[i].flag==0){
            num[i].flag=1;
            cout<<"请输入名字: "<<endl;
            cin>>num[i].name;
            //cin.ignore();是 C++ 标准库中 istream 类的一个成员函数，用于从输入流中丢弃字符，直到遇到指定的字符为止。它通常用于处理输入流中的换行符（'\n'），以避免这些换行符对后续输入操作的影响。
            cout<<"请输入性别:\n1-男性\n2-女性"<<endl;
            cin>>num[i].gender;
            cout<<"请输入年龄: "<<endl;
            cin>>num[i].age;
            cout<<"请输入联系电话: "<<endl;
            cin>>num[i].number;
            //getline(cin, num[i].number); 是 C++ 中用于从标准输入流 cin 读取一行字符串并存储到 num[i].number 变量中的语句。这个函数特别适用于读取包含空格的字符串，例如电话号码、地址等。
            cout<<"请输入家庭住址: "<<endl;
            cin>>num[i].home;           
            break;
        }
    }
    system("cls");
}

void Showcontacts(struct contacts num[]){
    for(int i=0;i<MAX;i++){
        if(num[i].flag==1){
            cout<<num[i].name<<"\t";
            if(num[i].gender==1){
                cout<<"男性\t";
            }else{
                cout<<"女性\t";
            }
            cout<<num[i].age<<"\t";
            cout<<num[i].number<<"\t";
            cout<<num[i].home<<endl;
        }
    }
    system("pause");
    system("cls");
}

void Deletecontacts(struct contacts num[]){
    string name;
    cin>>name;
    for(int i=0;i<MAX;i++){
        if(name==num[i].name){
            num[i].flag=0;
            cout<<"删除成功。"<<endl;
            goto here;
        }
    }
    cout<<"此人不存在"<<endl;
    here:
    system("cls");
}

void Findcontacts(struct contacts num[]){
    string name;
    cin>>name;
    for(int i=0;i<MAX;i++){
        if(name==num[i].name&&num[i].flag==1){
            cout<<num[i].name<<"\t";
            if(num[i].gender==1){
                cout<<"男性\t";
            }else{
                cout<<"女性\t";
            }
            cout<<num[i].age<<"\t";
            cout<<num[i].number<<"\t";
            cout<<num[i].home<<endl;
            goto here2;
        }
    }
    cout<<"此人不存在"<<endl;
    here2:
    system("pause");
    system("cls");
}

void Changecontacts(struct contacts num[]){
    string name;
    cin>>name;
    for(int i=0;i<MAX;i++){
        if(name==num[i].name&&num[i].flag==1){
            cout<<"请输入名字: "<<endl;
            cin>>num[i].name;
            cout<<"请输入性别:\n1-男性\n 2-女性"<<endl;
            cin>>num[i].gender;
            cout<<"请输入年龄: "<<endl;
            cin>>num[i].age;
            cout<<"请输入联系电话: "<<endl;
            cin>>num[i].number;
            cout<<"请输入家庭住址: "<<endl;
            cin>>num[i].home;          
            goto here3;
        }
    }
    cout<<"此人不存在"<<endl;
    here3:
    system("cls");
}

void empty(struct contacts num[]){
    for(int i=0;i<MAX;i++){
        num[i].flag=0;
    }
    system("cls");
}