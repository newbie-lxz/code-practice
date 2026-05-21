/*
可以对内置数据类型以及自定义数据类型的数据进行存储。
将数组中的数据存储到堆区。
构造函数中可以传入数组的容量。
提供对应的拷贝构造函数以及operator=防止浅拷贝问题。
提供尾插法和尾删法对数组中的数据进行增加和删除。
可以通过下标的方式访问数组中的元素。
可以获取数组中当前元素个数和数组的容量。
*/

#include"MyArray.hpp"
#include"Person.hpp"

void Print(MyArray<int> &arr)
{
    for(int i = 0; i < arr.GetSize(); i++)
    {
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
}

void PrintPerson(MyArray<Person> &arr)
{
    for(int i = 0; i < arr.GetSize(); i++)
    {
        cout<<arr[i].m_Name<<"\t"<<arr[i].m_Age<<endl;
    }
    cout<<endl;
}

void test01()
{
    MyArray<int> arr1(10);
    MyArray<int> arr2(arr1);
    MyArray<int> arr3(100);
    arr3 = arr1;
}

void test02()
{
    MyArray<int> arr(5);
    for(int i=0; i<5; i++)
    {
        arr.Push_Back(i);
    }
    cout<<"arr: "<<endl;
    Print(arr);
    cout<<"arr's capacity : "<<arr.GetCapacity()<<endl;
    cout<<"arr's size : "<<arr.GetSize()<<endl;
    arr.Pop_Bcak();
    Print(arr);
    cout<<"arr's capacity : "<<arr.GetCapacity()<<endl;
    cout<<"arr's size : "<<arr.GetSize()<<endl;
}

void test03()
{
    MyArray<Person> Arr(10);
    Person p1("lxz", 19);
    Person p2("gxy", 19);
    Person p3("kdz", 19);
    Person p4("cyq", 20);

    Arr.Push_Back(p1);
    Arr.Push_Back(p2);
    Arr.Push_Back(p3);
    Arr.Push_Back(p4);

    PrintPerson(Arr);
    cout<<"Arr's capacity : "<<Arr.GetCapacity()<<endl;
    cout<<"Arr's size : "<<Arr.GetSize()<<endl;
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}