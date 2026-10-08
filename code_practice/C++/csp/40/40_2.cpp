#include<iostream>
#include<vector>

using namespace std;

int g(int num1, int num2)
{
    int ans = num1*num1 + num2*num2;
    ans %= 8;
    return ans ^ num2;
}

int main()
{
    int n,m;
    vector<int> k(m);
    cin>>n>>m;
    for(int i=0; i<m; i++)
    {
        cin>>k[i];
    }
    while(n--)
    {
        int a;
        cin>>a;
        for(int i=m-1; i>=0; i--)
        {
            int temp1 = a / 64;
            int temp2 = ((a/8) % 8) ^ g(temp1, k[i]);
            int temp3 = (a%8)^g(temp2,k[i]);
            a = temp3*64 + temp1*8 + temp2;
        }
        cout<<a<<endl;
    }

    return 0;
}