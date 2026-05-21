#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

//sort(iterator beg, iterator end) //对beg和end区间内元素进行排序
void printDeque(const deque<int>&d)
{
    for(deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void test01()
{
    deque<int> d1;
    d1.push_back(10);
    d1.push_back(20);
    d1.push_back(30);
    d1.push_front(100);
    d1.push_front(200);
    d1.push_front(300);
    
    printDeque(d1);

    sort(d1.begin(), d1.end());             //升序
    printDeque(d1);

    sort(d1.rbegin(), d1.rend());
    printDeque(d1);
}

int main()
{
    test01();
    return 0;
}