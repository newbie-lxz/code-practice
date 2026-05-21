#include<algorithm>
#include<vector>
#include<string> 
#include<iostream>
using namespace std;
//vector容器嵌套容器(二维数组)

void test01()
{
    //大容器
    vector<vector<int>>v;
    //小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for(int i = 0; i < 4; i++)
    {
        v1.push_back(i+1);
        v2.push_back(i+2);
        v3.push_back(i+3);
        v4.push_back(i+4);
    }

    //将小容器放到大容器里
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for(vector<vector<int>> :: iterator i = v.begin(); i < v.end(); i++)
    {
        for(vector<int> :: iterator j = (*i).begin(); j < (*i).end(); j++)
        {
            cout<<(*j)<<"\t";
        }
        cout<<endl;
    }
}

int main()
{
    test01();
    return 0;
}