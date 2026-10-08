#include<iostream>
#include<vector>

using namespace std;

void one(vector<vector<char>>& mp, int a, int b, int c, int d, int e)
{
    int size = mp.size();

    // 题目坐标从1开始，数组下标从0开始
    a--;
    b--;

    while(e--)
    {
        // 先转置
        for(int i=1; i<size; i++)
        {
            for(int j=0; j<i; j++)
            {
                swap(mp[i][j], mp[j][i]);
            }
        }

        // 再左右翻转
        // 转置 + 左右翻转 = 顺时针90度
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size/2; j++)
            {
                swap(mp[i][j], mp[i][size-j-1]);
            }
        }
    }

    int times = d / 90;

    while(times--)
    {
        for(int i=1; i<c; i++)
        {
            for(int j=0; j<i; j++)
            {
                swap(mp[a+i][b+j], mp[a+j][b+i]);
            }
        }

        for(int i=0; i<c/2; i++)
        {
            for(int j=0; j<c; j++)
            {
                swap(mp[a+i][b+j],
                     mp[a+c-i-1][b+j]);
            }
        }
    }
}

void two(vector<vector<char>>& mp, int a, int b, int c, int d, int e)
{
    // 题目下标从1开始
    a--;
    b--;
    c--;
    d--;


    if(e == 1)
    {
        // 上下翻转

        // 只需要交换一半的行
        for(int i=a; i<a+(b-a+1)/2; i++)
        {
            // 注意这里必须 <= d
            // 因为题目的 l~r 两端都包含
            for(int j=c; j<=d; j++)
            {
                swap(mp[i][j],
                     mp[b-(i-a)][j]);
            }
        }
    }
    else
    {
        // 左右翻转

        // 只需要交换一半的列
        for(int i=c; i<c+(d-c+1)/2; i++)
        {
            // 注意这里必须 <= b
            for(int j=a; j<=b; j++)
            {
                swap(mp[j][i],
                     mp[j][d-(i-c)]);
            }
        }
    }
}


int main()
{
    int z;
    cin >> z;

    vector<vector<char>> mp(z, vector<char>(z));

    for(int i=0; i<z; i++)
    {
        for(int j=0; j<z; j++)
        {
            cin >> mp[i][j];
        }
    }

    int k;
    cin >> k;

    vector<int> key(k);

    for(int i=0; i<k; i++)
    {
        cin >> key[i];
    }

    int epch = key[0];

    int len = (key.size()-1) / 6;

    for(int i=len-1; i>=0; i--)
    {
        int op = key[6*i+1];

        int a = key[6*i+2];
        int b = key[6*i+3];
        int c = key[6*i+4];
        int d = key[6*i+5];
        int e = key[6*i+6];

        if(op == 1)
        {
            one(mp, a, b, c, d, e);
        }
        else
        {
            two(mp, a, b, c, d, e);
        }
    }

    int n = 0;
    int m = 0;

    // 求原图片的行数
    while(n < z && mp[n][0] != '?')
    {
        n++;
    }

    // 求原图片的列数
    while(m < z && mp[0][m] != '?')
    {
        m++;
    }


    cout << n << " " << m << endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cout << mp[i][j];
        }

        cout << endl;
    }

    return 0;
}