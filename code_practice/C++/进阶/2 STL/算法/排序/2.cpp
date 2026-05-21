#include<iostream>
#include<algorithm>
#include<ctime>
#include<vector>
using namespace std;

/*
random_shuffle
功能描述：
洗牌指定范围内的元素随机调整次序

函数原型：
random_shuffle(iterator beg, iterator end);
指定范围内的元素随机调整次序
beg 开始迭代器
end 结束迭代器
*/

void print(int v)
{
    cout<<v<<" ";
}

void test01()
{
    vector<int> v;
    for(int i=0; i<10; i++)
    {
        v.push_back(i);
    }
    for_each(v.begin(),v.end(),print);
    cout<<endl;

    random_shuffle(v.begin(),v.end());
    for_each(v.begin(),v.end(),print);
    cout<<endl;
}

int main()
{
    srand(time(0));
    //srand((unsigned int)time(NULL));
    test01();

    return 0;
}