#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
int n,m,k;
vector<vector<int>> a;

ll to_ll(vector<int> &v)
{
    ll res = 0;
    for(int i=v.size()-1;i>=0;i--)
    {
        res *= k;
        res += v[i];
    }
    return res;
}

int main()
{
    cin>>n>>m>>k;
    a.resize(n);
    for(int i=0;i<n;i++)
    {
        ll temp;
        cin>>temp;
        vector<int> temp_k;
        while(temp)
        {
            temp_k.push_back(temp%k);
            temp/=k;
        }
        a[i] = temp_k;
    }

    while(m--)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            int l,r;
            ll v;
            cin>>l>>r>>v;
            vector<int> v_k;
            while(v)
            {
                v_k.push_back(v%k);
                v/=k;
            }
            for(int i=l-1;i<r;i++)
            {
                if(a[i].size()<v_k.size())
                {
                    for(int j=0;j<a[i].size();j++)
                    {
                        a[i][j] += v_k[j];
                        a[i][j] %= k;
                    }
                    for(int j=a[i].size();j<v_k.size();j++)
                    {
                        a[i].push_back(v_k[j]);
                    }
                }
                else
                {
                    for(int j=0;j<v_k.size();j++)
                    {
                        a[i][j] += v_k[j];
                        a[i][j] %= k;
                    }
                }
            }
        }
        else
        {
            int l,r;
            cin>>l>>r;
            vector<ll> temp;
            for(int i=l-1;i<r;i++)
            {
                temp.push_back(to_ll(a[i]));
            }
            sort(temp.begin(),temp.end(),greater<ll>());
            vector<vector<int>> temp_k(r-l+1);
            for(int i=0;i<r-l+1;i++)
            {
                int curr = temp[i] % k;
                temp_k[i].push_back(curr*(curr+1)/2 % k);

                int times = 2;
                while(temp[i]>=(ll)pow(k,times-1))
                {
                    curr = temp[i] % (ll)pow(k,times);
                    int num = curr / (ll)pow(k,times-1);
                    curr = curr % k;
                    temp_k[i].push_back(num * (curr + 1) % k);
                    times++;
                }
            }
            for(int i=0;i<temp_k[0].size();i++)
            {
                for(int j=1; j<r-l+1; j++)
                {
                    if(i<temp_k[j].size())
                    {
                        temp_k[0][i] += temp_k[j][i];
                        temp_k[0][i] %= k;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            ll ans = 0;
            for(int i=temp_k[0].size()-1;i>=0;i--)
            {
                ans *= k;
                ans += temp_k[0][i];
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}