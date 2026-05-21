/*
void 排序(int dp[],int n)
{
    int i,j,k,l;
    for(i=0;i<n-1;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(dp[j]>dp[k]){
                k=j;
            }
        }
        if(k!=i){
            dp[l]=dp[k];
            dp[k]=dp[i];
            dp[i]=dp[l];
        }
    }
}
*/