#include<iostream>
#include<map>
using namespace std;

class myCompare
{
    public:
        bool operator()(int num1, int num2)
        {
            return num1 > num2;
        }
};

void printMap(map<int,int,myCompare> &m)
{
    for(map<int,int,myCompare>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout<<"key = "<<(*it).first << "\tvalue = "<<(*it).second<<endl;
    }
    cout<<endl;
}

void test01()
{
    map<int,int,myCompare> mp;
    mp.insert(pair<int, int>(1,10));
    mp.insert(pair<int, int>(5,100));
    mp.insert(pair<int, int>(3,110));
    mp.insert(pair<int, int>(4,0));
    mp.insert(pair<int, int>(2,98));
    printMap(mp);
}

int main()
{
    test01();
    return 0;
}