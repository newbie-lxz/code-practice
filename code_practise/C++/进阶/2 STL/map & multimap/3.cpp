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
    mp.insert(pair<int,int>(1,10));
    mp.insert(make_pair(2,20));
    mp.insert(map<int,int>::value_type(3,30));
    printMap(mp);
    mp[4] = 40;                         //不建议
    cout<<mp[5]<<endl;
    printMap(mp);
    
    mp.erase(mp.begin());
    printMap(mp);

    mp.erase(3);
    printMap(mp);                       //删除key = 3;

    mp.erase(mp.begin(), mp.end());
    //mp.clear();
    printMap(mp);
}

int main()
{
    test01();
    return 0;
}