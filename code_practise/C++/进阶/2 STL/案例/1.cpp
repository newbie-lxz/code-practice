#include<iostream>
#include<algorithm>
#include<deque>
#include<vector>
using namespace std;

void test01()
{
    vector<deque<float>> v(5);
    for(int i=0; i<5; i++)
    {
        deque<float> d;
        for(int j=0; j<10; j++)
        {
            float score;
            cin>>score;
            d.push_back(score);
        }
        v[i] = d;
        sort(v[i].begin(), v[i].end());
        v[i].pop_back();
        v[i].pop_front();

        float sum=0;
        for(int j=0; j<8; j++)
        {
            sum+=v[i][j];
        }
        v[i].push_back(sum/8);
    }
    for(int i=1; i<=5; i++)
        cout<<"第"<<i<<"号选手最终得分为： "<<v[i-1][8]<<endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
