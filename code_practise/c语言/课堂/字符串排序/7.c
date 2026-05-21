#define M 8 
#define N 5 
#include <stdio.h> 
void merge(int x[], int s, int y[], int t);
int main() 
{
    int x[M]={-7,1,3,5,7,9,12,45}, y[N]={0,2,4,6,8} ;
    merge(x,M,y,N);
    return 0;
}

void merge(int x[], int s, int y[], int t)
{
    int xy[s + t];
    int i = 0, j = 0, k = 0;

    while (i < s && j < t){
        if (x[i] < y[j])
        {
            xy[k] = x[i];
            i++;
            k++;
        }
        else
        {
            xy[k] = y[j];
            j++;
            k++;
        }}
    while (i < s)
    {
        xy[k] = x[i];
        i++;
        k++;
    }
    while (j < s)
    {
        xy[k] = y[j];
        j++;
        k++;
    }
    printf("\n%d 个有序数为：", s + t);
    for (i = 0; i < s + t; i++)
        printf("%d,", xy[i]);
}