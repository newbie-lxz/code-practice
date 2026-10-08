#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>
#include<deque>
#include<vector>
#include<sstream>
using namespace std;

#define MOD 1000000007

int main()
{
    int n;
    cin>>n;
    cin.ignore();
    unordered_map<string,int> mp;
    unordered_map<string,vector<string>> mps;
    while(n--)
    {
        string s;
        getline(cin,s);
        stringstream ss(s);
        string type;
        string var;
        ss>>type;
        ss>>var;
        if(type=="1")
        {
            int ans = 0;
            while(ss>>s)
            {
                if(s[0]=='$')
                {
                    s = s.substr(1);
                    if(mp.count(s))
                    {
                        ans+=mp[s];
                        ans%=MOD;
                    }
                    else
                    {
                        stack<string> ds;
                        ds.push('$'+s);
                        while(!ds.empty())
                        {
                            string top = ds.top();
                            ds.pop();
                            if(top[0]!='$')
                            {
                                ans+=top.size();
                                ans%=MOD;
                            }
                            else
                            {
                                top = top.substr(1);
                                if(mp.count(top))
                                {
                                    ans+=mp[top];
                                    ans%=MOD;
                                }
                                else
                                {
                                    for(int i=0; i<mps[top].size(); i++)
                                    {
                                        ds.push(mps[top][i]);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    ans+=s.size();
                    ans%=MOD;
                }
            }
            mps.erase(var);
            mp[var] = ans;
        }
        else if(type=="2")
        {
            mp.erase(var);
            vector<string> ans;
            while(ss>>s)
            {
                ans.push_back(s);
            }
            mps[var] = ans;
        }
        else
        {
            if(mp.count(var))
            {
                cout<<mp[var]<<endl;
            }
            else
            {
                int ans = 0;
                stack<string> ds;
                ds.push('$'+var);
                while(!ds.empty())
                {
                    string top = ds.top();
                    ds.pop();
                    if(top[0]!='$')
                    {
                        ans+=top.size();
                        ans%=MOD;
                    }
                    else
                    {
                        top = top.substr(1);
                        if(mp.count(top))
                        {
                            ans+=mp[top];
                            ans%=MOD;
                        }
                        else
                        {
                            for(int i=0; i<mps[top].size(); i++)
                            {
                                ds.push(mps[top][i]);
                            }
                        }
                    }
                }
                cout<<ans<<endl;
            }
        }
    }
    return 0;
}