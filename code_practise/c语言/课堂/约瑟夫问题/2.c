#include<stdio.h>
void josephus(int k,int N,int m)
{
    int dp[N];
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
    }
    
    for(int n=1;n<N;n++){
        int t=1;
        while(t<=m){
            if(dp[k-1]==1){
                t++;                //只有下一个报数的是活人才能报下一个数
            }
            k++;
            if(k>=N+1){
                k-=N;
            }
        }
        int u=k;
        if(u==1){
            u=N+1;
        }
        dp[u-2]=0;                //死亡的人代号为零，用来判断是否跳过
        printf("第%d次%d号死亡。\n",n,u-1);
    }
    for(int c=0;c<N;c++){
        if(dp[c]==1){
            printf("第%d号存活。",c+1);
        }
    }
}
int main()
{
    int k,N,m;                          //从第k个开始，有N个人，报m号的人死
    int find=0;
    
    do{
    printf("请输入开始任务的编号,总人数和报几号的个人死：");
    scanf("%d %d %d",&k,&N,&m);
    if(k>N||k<=0||N<=1||m<=0){
        find=1;                
    }
    }while(find==1);                  //判断输入是否合理
    
    josephus(k,N,m);
    return 0;
}
