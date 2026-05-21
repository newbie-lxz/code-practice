#include<iostream>
using namespace std;
//静态多态：函数重载 和 运算符重载 属于静态多态，复用函数名
//         函数地址早绑定 - 编译阶段确定函数地址
//动态多态：派生类 和 虚函数 实现运行时多态
//         函数地址晚绑定 - 运行阶段确定函数地址

class Animal
{
    public:
        void speak()
        {
            cout<<"动物在说话。"<<endl;
        }

        virtual void speak2()                           //此函数地址无法提前确定
        {
            cout<<"2动物在说话。"<<endl;
        }
};
//动态多态满足条件
//1、有继承关系
//2、子类重写父类的虚函数   如36行（重写：返回值类型 函数名 参数列表 完全一致）

//动态多态的使用
//1、父类的指针或者引用 指向子类对象， 如42行是引用形式

class Cat : public Animal
{
    public:
        void speak()                                    
        {
            cout<<"小猫在说话。"<<endl;
        }

        void speak2()                                   //子类重写前面加不加virtual都可以，可以在()后面加上override来标识重写，并在父类未有对应虚函数时报错，增强可读性和安全性
        {
            cout<<"2小猫在说话。"<<endl;
        }
};

void dospeak(Animal &animal)
{
    animal.speak();                         //输出Animal的speak    因为speak()的地址是早绑定，在编译阶段就确定了地址，已经确定好是Animal的speak无论你传入什么
    animal.speak2();                        //输出animal对应类型的speak       因为speak2()加了virtual，地址晚绑定
}

void test01()
{
    Cat cat;
    dospeak(cat);                           //42行定义时用的Animal，父类的引用接收子类的对象
}

int main()
{
    test01();
    cout<<sizeof(Animal)<<endl;
    return 0;
}