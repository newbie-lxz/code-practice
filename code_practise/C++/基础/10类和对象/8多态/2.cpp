#include<iostream>
using namespace std;
//多态的深入剖析

class Animal
{
    public:
        virtual void speak()
        {
            cout<<"动物在说话。"<<endl;
        }
};

class Cat : public Animal
//继承了父类的全部包括虚函数表
//子类的虚函数指针指向vftable,里面内容也是&Animal::speak,但是子类发生了重写，覆盖了内容成为&Cat::speak
{
    public:
        void speak()                                    
        {
            cout<<"小猫在说话。"<<endl;
        }
};

class Dog : public Animal
{
    public:
        void speak()
        {
            cout<<"小狗在说话。"<<endl;
        }
};

void dospeak(Animal &animal)
{
    animal.speak();                         
}

void test01()
{
    Cat cat;
    dospeak(cat);    
    Dog dog;
    dospeak(dog);                       
}

void test02()
{
    cout<<"sizeof(Animal) = "<<sizeof(Animal)<<endl;                
    //第8行无virtual输出1，有则输出8(根据电脑系统而定，x86为4，x64为8)，是一个虚函数(表)指针vfptr：virtual-function-pointer(指针)，指向一个虚函数表vftable
    //vftable：virtual-function-table  表内部记录一个虚函数地址 &Animal::speak
}

int main()
{
    test01();
    test02();
    return 0;
}