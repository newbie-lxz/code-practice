#include<iostream>
#include<deque>
using namespace std;

//双端数组，可以对头部进行插入删除操作
//vector对于头部的删除插入效率低，数据量越大，效率月低
//deque相对而言，对头部的插入删除速度会比vector快
//vector访问元素的速度会比deque快

/*
deque<T> deqT;                  默认构造形式
deque(beg, end);                构造函数将 [beg, end) 区间中的元素拷贝给本身
deque(n, elem);                 构造函数将 n 个 elem 拷贝给本身
deque(const deque &deq);        拷贝构造函数
*/

void printDeque(const deque<int> d)
{
    for(deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}//只读的话迭代器也得是const_的

void test01()
{
    deque<int>d1;
    for(int i=0; i<10; i++)
    {
        d1.push_back(i);
    }
    printDeque(d1);

    deque<int>d2(d1.begin(), d1.end());
    printDeque(d2);

    deque<int>d3(10,100);
    printDeque(d3);

    deque<int>d4(d3);
    printDeque(d4);
}

int main()
{
    test01();
    return 0;
}