#include<stdio.h>
int any(int count,int m){
    while(count>0){
        if((count%10)==m){
            return 1;
        }
        count/=10;
    }
    return 0;
}
void order(int n,int m){
    int people[n];
    for(int i=0;i<n;i++){
        people[i]=i+1;
    }
    int current=0;
    int count=1;
    int mid=0;
    while(n>1){
        if(count%7==0||any(count,m)==1){
            current=(current+count-1-mid)%n;
            mid=count;
            printf("%d -> ",people[current]);
            for (int i = current; i < n - 1; i++) {
                people[i] = people[i + 1];
            }
            n--;
        }
        count++;
    }
    printf("%d",people[0]);
}
int main()
{
    int n,m;
    do{
        scanf("%d %d",&n,&m);
    }while(n<m||m<2||m>9);
    order(n,m);
    return 0;
}