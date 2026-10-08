# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;
vector<pair<int,int>> v1 = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
                            {1,0},{1,3},{1,6},{1,8},
                            {2,0},{2,3},{2,4},{2,5},{2,6},{2,7},
                            {3,0},{3,5},{3,6},
                            {4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6}
                            };

vector<pair<int,int>> v2 = {{1,1},{1,2},{1,4},{1,5},{1,7},
                            {2,1},{2,2},{2,8},
                            {3,1},{3,2},{3,3},{3,4},{3,7},{3,8},
                            {4,7},{4,8}
                            };

int main()
{
    int n,l;
    cin>>n>>l;
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> ans;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>a[i][j];
        }
    }
    int lend = n-9; 
    int uend = n-5;
    for(int i=0; i<=uend; i++)
    {
        for(int j=0; j<=uend; j++)
        {
            int num1 = l;
            int num2 = -1;
            for(int k=0; k<v1.size(); k++)
            {
                int x = i + v1[k].first;
                int y = j + v1[k].second;
                if(a[x][y]<num1)
                {
                    num1 = a[x][y];
                }
            }
            for(int k=0; k<v2.size(); k++)
            {
                int x = i + v2[k].first;
                int y = j + v2[k].second;
                if(a[x][y]>num2)
                {
                    num2 = a[x][y];
                }
            } 
            if(num1>num2)
            {
                for(int k=num2+1; k<=num1; k++)
                {
                    ans.push_back(k);
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    for(int i=0; i<ans.size(); i++)
    {
        cout<<ans[i]<<" ";
    }
    return 0;
}