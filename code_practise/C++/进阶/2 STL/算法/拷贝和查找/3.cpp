#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
replace_if
功能描述：
将区间内满足条件的元素，替换成指定元素

函数原型：
replace_if(iterator beg, iterator end, _pred, newvalue);
按条件替换元素，满足条件的替换成指定元素
beg 开始迭代器
end 结束迭代器
_pred 谓词
newvalue 替换的新元素
*/


void print(int val)
{
    cout<<val<<"\t";
}

class replaceGreater20
{
    public:
        bool operator()(int val)
        {
            return val>20;
        }
};

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(50);
    v.push_back(30);
    v.push_back(10);
    v.push_back(30);

    for_each(v.begin(),v.end(),print);
    cout<<endl;

    replace_if(v.begin(),v.end(),replaceGreater20(),250);
    for_each(v.begin(),v.end(),print);
    cout<<endl;
}

int main()
{
    test01();

    return 0;
}