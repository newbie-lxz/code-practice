#include<iostream>
using namespace std;
//c++编译器至少给一个类添加4个函数
/*
默认构造函数
默认析构函数
默认拷贝构造函数
赋值运算符operator=，对属性进行值拷贝
*/
//赋值运算符重载
class person
{
    public:
        person(int age)
        {
            m_age = new int(age);
        }
        ~person()
        {
            if(m_age!=NULL)
            {
                delete m_age;
                m_age = NULL;
            }
        }
        person &operator=(person &p)
        {
            //编译器是提供浅拷贝
            //m_age = p.m_age;

            //应该先判断是否有属性在堆区，如果有先释放干净，然后再深拷贝
            if(m_age!=NULL)
            {
                delete m_age;
                m_age = NULL; 
            }
            m_age = new int(*p.m_age);
            return *this;
        }//重载赋值运算符

        int *m_age;
};

void test01() 
{
    person p1(18); 
    person p2(20);
    person p3(30);
    cout<<"p1.age = "<<p1.m_age<<endl;
    cout<<*p1.m_age<<endl;
    cout<<"p2.age = "<<p2.m_age<<endl;
    cout<<*p2.m_age<<endl;
    p2 = p1;
    cout<<"p1.age = "<<p1.m_age<<endl;
    cout<<*p1.m_age<<endl;
    cout<<"p2.age = "<<p2.m_age<<endl;
    cout<<*p2.m_age<<endl;                     //没有26~38出错p2的所有数据都和p1相同，两个对象的m_age都指向同一片内存空间，这时析构函数释放内存会重复释放同一个内存空间
    p3 = p2 = p1;
    cout<<*p1.m_age<<*p2.m_age<<*p3.m_age<<endl;
}



int main()
{
    test01();
    return 0;
}