#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string,char> code_map;
vector<string> vs = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
string trans(string s)
{
    if(s[0]=='H')
    {
        if(s[1]=='H')
        {
            return s.substr(1);
        }
        else
        {
            string str;
            for(int i=1; i<=s.size()-3; i++)
            {
                if(s[i]>='0' && s[i]<='9')
                {
                    str+=vs[s[i]-'0'];
                }
                else
                {
                    str+=vs[s[i]-'a'+ 10];
                }
            }
            int num = s[s.size()-1] - '0';
            str.resize(str.size()-num);
            string start;
            string ans;
            for(int i=0; i<str.size(); i++)
            {
                start+=str[i];
                if(code_map.count(start))
                {
                    ans+=code_map[start];
                    start.clear();
                }
            }
            return ans;
        }
    }
    else
    {
        return s;
    }
}

int main()
{
    int s,d;
    cin>>s>>d;
    vector<pair<string,string>> statics_table(s+1);
    deque<pair<string,string>> dynamic_table;
    for(int i=1; i<=s; i++)
    {
        cin>>statics_table[i].first>>statics_table[i].second;
    }
    for(int i=1; i<=s; i++)
    {
        statics_table[i].first = trans(statics_table[i].first);
        statics_table[i].second = trans(statics_table[i].second);
    }
    string str;
    deque<char> dq;
    cin>>str;
    for(int i=0;i<str.size(); i++)
    {
        if(str[i] == '1')
        {
            string temp;
            for(int j=0; j<dq.size(); j++)
            {
                temp += dq[j];
            }
            code_map[temp] = str[i+1];
            i++;
            while(!dq.empty() && dq.back()=='1')
            {
                dq.pop_back();
            }
            if(!dq.empty())
            {
                dq.pop_back();
                dq.push_back('1');
            }
        }
        else
        {
            dq.push_back('0');
        }
    }
    int n;
    cin>>n;
    while(n--)
    {
        int command;
        cin>>command;
        if(command==1)
        {
            int i;
            cin>>i;
            if(i<=s) 
            {
                cout<<statics_table[i].first<<": "<<statics_table[i].second<<endl;
            }   
            else
            {
                i-=s+1;
                cout<<dynamic_table[i].first<<": "<<dynamic_table[i].second<<endl;
            }  
        }
        else if(command == 2)
        {
            int flag;
            cin>>flag;
            string k,v;
            if(flag==0)
            {
                
                cin>>k>>v;
                k = trans(k);
                v = trans(v);
            }
            else
            {
                cin>>v;
                if(flag<=s)
                {
                    k = statics_table[flag].first;
                }
                else
                {
                    flag-=s+1;
                    k = dynamic_table[flag].first;
                }
                v = trans(v);
            }
            cout<<k<<": "<<v<<endl;
            if(dynamic_table.size()==d)
            {
                dynamic_table.pop_back();
            }
            dynamic_table.push_front({k,v});
        }
        else
        {
            int flag;
            cin>>flag;
            string k,v;
            if(flag==0)
            {
                
                cin>>k>>v;
                k = trans(k);
                v = trans(v);
            }
            else
            {
                cin>>v;
                if(flag<=s)
                {
                    k = statics_table[flag].first;
                }
                else
                {
                    flag-=s+1;
                    k = dynamic_table[flag].first;
                }
                v = trans(v);
            }
            cout<<k<<": "<<v<<endl;
        }
    }
    return 0;
}