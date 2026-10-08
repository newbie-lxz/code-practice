#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

const double eps = 1e-8;

//灵活任务结构体
struct FlexItem
{
    int a;
    int b;
    double rate;
};

//普通任务结构体（0‑1）
struct HardItem
{
    int a;
    int b;
};

// 给定剩余咖啡rem，返回灵活任务可以拿到的最大收益
double calcFlex(double rem, const vector<FlexItem>& flex,
                const vector<double>& preCost, const vector<double>& preGain)
{
    if (rem < eps) return 0.0;
    int sz = flex.size();
    //全部灵活任务都拿满
    if(rem >= preCost.back()-eps)
    {
        return preGain.back();
    }
    //二分找到最后一个可以完整买下的下标
    int pos = upper_bound(preCost.begin(),preCost.end(),rem+eps)-preCost.begin()-1;
    double total = preGain[pos];
    double left = rem - preCost[pos];
    if(pos < sz)
    {
        total += left * flex[pos].rate;
    }
    return total;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double m;
    double sumTime = 0;
    vector<FlexItem> flex;
    vector<HardItem> hard;

    cin >> n >> m;
    for(int i = 0;i < n;i++)
    {
        int o, t, a, b;
        cin >> o >> t >> a >> b;
        sumTime += t;
        if(o == 0)
        {
            flex.push_back({a,b, 1.0*b/a});
        }
        else
        {
            hard.push_back({a,b});
        }
    }

    //灵活任务按单位收益降序排序
    sort(flex.begin(),flex.end(),[](const FlexItem& x,const FlexItem& y){
        return x.rate > y.rate + eps;
    });

    //预处理前缀和数组
    int fsz = flex.size();
    vector<double> preCost(fsz+1,0.0), preGain(fsz+1,0.0);
    for(int i = 0;i < fsz;i++)
    {
        preCost[i+1] = preCost[i] + flex[i].a;
        preGain[i+1] = preGain[i] + flex[i].b;
    }

    int k = hard.size();
    double maxCut = 0.0;
    //枚举所有普通任务子集，mask遍历
    for(int mask = 0;mask < (1 << k);mask++)
    {
        double costH = 0;
        double gainH = 0;
        for(int i = 0;i < k;i++)
        {
            if(mask & (1 << i))
            {
                costH += hard[i].a;
                gainH += hard[i].b;
            }
        }
        if(costH > m + eps) continue;
        double rem = m - costH;
        double gainF = calcFlex(rem, flex, preCost, preGain);
        maxCut = max(maxCut, gainH + gainF);
    }

    double ans = sumTime - maxCut;
    printf("%.6lf\n",ans);
    return 0;
}
