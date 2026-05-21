#include<iostream>
#include<map>
using namespace std;

void printMap(map<int,int> &m)
{
    for(map<int,int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout<<"key = "<<(*it).first << "\tvalue = "<<(*it).second<<endl;
    }
    cout<<endl;
}

void test01()
{
    map<int,int> mp;
    mp.insert(pair<int,int>(1,100));
    mp.insert(pair<int,int>(12,1000));
    mp.insert(pair<int,int>(190,1000));

    if(mp.empty())
    {
        cout<<"空的。"<<endl;
    }
    else
    {
        cout<<"非空。"<<endl;
        cout<<mp.size()<<endl;
    }
}

void test02()
{
    map<int,int> mp;
    mp.insert(pair<int,int>(11,100));
    mp.insert(pair<int,int>(12,1000));
    mp.insert(pair<int,int>(190,1000));

    map<int,int> mp2;
    mp2.insert(pair<int,int>(10,100));
    mp2.insert(pair<int,int>(120,200));
    mp2.insert(pair<int,int>(19,000));

    mp.swap(mp2);
    printMap(mp);
    printMap(mp2);
}

int main()
{
    test01();
    test02(); 
    return 0;
}