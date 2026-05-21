#include<stdio.h>
void order(int n, int num[]);      //排序
int found(int num[],int low,int high,int q);
int main()
{
    int n,q,low,high;
    do{
        printf("请输入待排序数字的个数：\n");
        scanf("%d",&n);
    }while(n<1);

    int num[n];
    printf("请输入待排序数字：\n");
    for(int i=0; i<n; i++){
        scanf("%d",&num[i]);
    }

    order(n, num);                  //排序
    
    printf("请输入你要查找的数字：\n");
    scanf("%d",&q);
    high = n-1;
    low = 0;

    int result = found(num,low,high,q);
    if(result==-1){
        printf("您要找的数字不在其中。\n");
    }else{
        printf("您要找的数字排在%d位,是%d。\n",result+1,num[result]);
    }
    return 0;
}

void order(int n, int num[])       //排序
{
    int i,j;
    for(j=0; j<n; j++){
        int k=0;
        for(i=0; i<n-1-j; i++){
            int mid=0;
            if(num[i]>num[i+1]){
                mid=num[i];
                num[i]=num[i+1];
                num[i+1]=mid;
                k++;
            }
        }
        if(k==0){
            for(int m=0;m<n;m++){
                printf("%d  ",num[m]);
            }
            printf("\n");
            break;
        }
    }
}

int found(int num[],int low,int high,int q) //查找
{
    int mid;
    mid = low + (high - low)/2;
    if(high>=low){
        if(q > num[mid]){
            low = mid + 1;
            return found(num, low, high, q);
        }else if(q < num[mid]){
            high = mid - 1;
            return found(num, low, high, q);
        }else{ 
            return mid;
        }
    }
    return -1;
}