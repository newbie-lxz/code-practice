#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        cin >> a[i];
    }
    vector<vector<int>> S(m);
    vector<int> _xor(m, 0);
    for(int i=0; i<m; i++)
    {
        int num;
        cin>>num;
        while(num--)
        { 
            int x;
            cin>>x;
            S[i].push_back(x);
            _xor[i]^=a[x-1];
        }
        sort(S[i].begin(), S[i].end());
    }
    for(int i=0; i<m; i++)
    {
        int num;
        cin>>num;
        int temp_xor = 0;
        bool flag = true;
        for(int j=0; j<num; j++)
        {
            int x;
            cin>>x;
            if(x!=S[i][j])
            {
                flag = false;
            }
            temp_xor ^= a[x-1];
        }
        if(flag ^ (temp_xor == _xor[i]))
        {
            cout<<"wrong"<<endl;
        }
        else
        {
            cout<<"correct"<<endl;
        }
    }
    return 0;
}