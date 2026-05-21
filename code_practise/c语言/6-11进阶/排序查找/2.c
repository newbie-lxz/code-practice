/*
int 查找(long dp[], long x, int n)
{
    int low = 0, high = n-1, mid;
    int pos = -1;
    int find = 0;
    while(!find && low <= high)
    {
        mid = low + (high - low)/2;
        if(x > do[mid])
        {
            low = mid + 1;
        }else if(x < dp[mid])
        {
            high = mid - 1;
        }else
        {
            pos = mid;
            find = 1;
        }
    }
    return pos;
}
*/