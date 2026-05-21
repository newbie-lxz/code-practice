#include"Person.h"

template<class T1, class T2>
Person<T1,T2> :: Person(T1 name, T2 age)
{
    this->m_name = name;
    this->m_age = age;
}

template<class T1, class T2>        
void Person<T1,T2>::showPerson()    
{
    cout<<"name : " <<m_name<<"\t"<<"age : "<<m_age<<endl;
}