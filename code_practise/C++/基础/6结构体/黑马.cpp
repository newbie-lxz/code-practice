#include<iostream>
#include<string>
#define MAX 1000
using namespace std;
struct contacts{
    string name;
    int gender;
    int age;//int8_t 较小内存，储存-128~127，占用一个字节；
    string number;
    string home;
};

struct Addressbook{
    contacts people[MAX];
    int quantity; 

};
void Menu();
int isExist(Addressbook *abs, string name);
void Newcontacts(struct Addressbook *abs);
void Showcontacts(struct Addressbook *abs);
void Deletecontacts(struct Addressbook *abs);
void Findcontacts(struct Addressbook *abs);
void Changecontacts(struct Addressbook *abs);
void empty(struct Addressbook *abs);

int main(){
    Addressbook abs;
    abs.quantity=0; 
    int command=7;
    do{
        Menu();  
        cin >> command;
        switch(command){
            case 1:
                Newcontacts(&abs);
                break;
            case 2:
                Showcontacts(&abs);
                break;
            case 3:
                Deletecontacts(&abs);
                break;
            case 4:
                Findcontacts(&abs);
                break;
            case 5:
                Changecontacts(&abs);
                break;
            case 6:
                empty(&abs);
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

int isExist(Addressbook *abs, string name){
    for(int i=0;i<abs->quantity;i++)
    {
        if(abs->people[i].name==name){
            return i;
        }
    }
    return -1;
}

void Newcontacts(struct Addressbook *abs){
    if(abs->quantity==MAX){
        return;
    }else{
        string name;
        cout<<"请输入姓名:\t"<<endl;
        cin>>name;
        abs->people[abs->quantity].name = name;

        cout<<"请输入性别:\t"<<endl;
        cout<<"1————男"<<endl;
        cout<<"2————女"<<endl;
        int sex=0;
        while(true){
            cin>>sex;
            if(sex==1||sex==2){
                abs->people[abs->quantity].gender=sex;
                break;
            }
            cout<<"输入有误，请重新输入"<<endl;
        }

        cout<<"请输入年龄：  "<<endl;
        int age = 0;
        cin>>age;
        abs->people[abs->quantity].age=age;

        cout<<"请输入电话号码:"<<endl;
        string number;
        cin>>number;
        abs->people[abs->quantity].number=number;

        cout<<"请输入家庭住址："<<endl;
        string home;
        cin>>home;
        abs->people[abs->quantity].home=home;

        abs->quantity++;

        cout<<"添加成功"<<endl;
        system("pause");
        system("cls");
    }
}

void Showcontacts(struct Addressbook *abs){
    if(abs->quantity==0){
        cout<<"无联系人"<<endl;
        system("pause");
        system("cls");
        return;
    }else{
        for(int i=0;i<abs->quantity;i++){
            cout<<abs->quantity<<". ";
            cout<<abs->people[i].name<<"\t";
            cout<<(abs->people[i].gender == 1 ? "男" : "女")<<"\t";
            cout<<abs->people[i].age<<"\t";
            cout<<abs->people[i].number<<"\t";
            cout<<abs->people[i].home<<"\n";
        }
    }
    system("pause");
    system("cls");
}

void Deletecontacts(struct Addressbook *abs){
    cout<<"请输入您要删除的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1){
        for(int i=ret; i<abs->quantity; i++){
            abs->people[i]=abs->people[i+1];
        }
        abs->quantity--;
        cout<<"删除成功"<<endl;
    }else{
        cout<<"查无此人"<<endl;
    }
    system("pause");
    system("cls");
}

void Findcontacts(struct Addressbook *abs){
    cout<<"请输入您要查找的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1){
        cout<<abs->people[ret].name<<"\t";
        cout<<(abs->people[ret].gender == 1 ? "男" : "女")<<"\t";
        cout<<abs->people[ret].age<<"\t";
        cout<<abs->people[ret].number<<"\t";
        cout<<abs->people[ret].home<<"\n";
    }else{
        cout<<"查无此人"<<endl;
    }
    system("pause");
    system("cls");
}

void Changecontacts(struct Addressbook *abs){
    cout<<"请输入您要更改的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1){
        cout<<"请输入姓名:\t"<<endl;
        cin>>name;
        abs->people[ret].name = name;

        cout<<"请输入性别:\t"<<endl;
        cout<<"1————男"<<endl;
        cout<<"2————女"<<endl;
        int sex=0;
        while(true){
            cin>>sex;
            if(sex==1||sex==2){
                abs->people[ret].gender=sex;
                break;
            }
            cout<<"输入有误，请重新输入"<<endl;
        }

        cout<<"请输入年龄：  "<<endl;
        int age = 0;
        cin>>age;
        abs->people[ret].age=age;

        cout<<"请输入电话号码:"<<endl;
        string number;
        cin>>number;
        abs->people[ret].number=number;

        cout<<"请输入家庭住址："<<endl;
        string home;
        cin>>home;
        abs->people[ret].home=home;

        cout<<"修改成功"<<endl;
    }else{
        cout<<"查无此人"<<endl;
    }
    system("pause");
    system("cls");
}

void empty(struct Addressbook *abs){
    abs->quantity = 0;
    cout << "通讯录已清空" <<endl;
    system("pause");
    system("cls");
}