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
    mp.insert(pair<int, int>(1,10));
    mp.insert(pair<int, int>(5,100));
    mp.insert(pair<int, int>(3,110));
    mp.insert(pair<int, int>(4,0));
    mp.insert(pair<int, int>(2,98));

    map<int,int>::iterator pos = mp.find(3);
    if(pos!=mp.end())
    {
        cout<<"find it!"<<"\t"<<pos->first<<"\t"<<pos->second<<endl;
    } 
    else
    {
        cout<<"not find."<<endl;
    }

    cout<<mp.count(3)<<endl;
}

int main()
{
    test01();
    return 0;
}