#include<stdio.h>
int main()
{
    int n;
    int trans=0;
    int count=0;
    printf("请输入一个数字:n (0<n<1000):\n");
    scanf("%d",&n);
    printf("请输入n个0或1:\n");
    char lg[n];
    for(int i=0;i<n;i++){
        scanf("%c",&lg[i]);
    }
    for(int i=0;i<n;i++){
        if(lg[i]=='1'){
            count++;
        }else{
            if(trans<=count){
                trans=count;
            }
            count=0;
        }
    }
    if(count > trans){
        trans = count;
    }
    printf("最多连续%d个",trans);
    return 0;
}