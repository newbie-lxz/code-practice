#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin>>n>>m;
    vector<int> day_apple(m+1);
    for(int i=1; i<=m; i++)
    {
        cin>>day_apple[i];
    }

    vector<int> best(n+1,0);
    best[1] = day_apple[1];
    for(int i=2; i<=n; i++)
    {
        int temp = 0;
        for(int j=1; i>=j && j<=m; j++)
        {
            temp = max(temp, best[i-j]+day_apple[j]);
        }
        best[i] = temp;
    }
    cout<<best[n];
    return 0;
}