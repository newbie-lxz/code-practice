#include<stdio.h>
#include<stdlib.h>

#define N 8
int queen[N][N];
int number=0;

int position(int row,int col)
{
    for(int i=0;i<row;i++){
        if(queen[i][col]){
            return 0;
        }
    }
    for(int i=row,j=col;i>=0&&j>=0;i--,j--){
        if(queen[i][j]){
            return 0;
        }
    }
    for(int i=row,j=col;i>=0&&j<8;i--,j++){
        if(queen[i][j]){
            return 0;
        }
    }
    return 1;
}

int way(int row)
{
    if(row==N){
        number++;
        printf("way %d\n",number);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                printf("%d ",queen[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }

    int mark=0;
    for (int col = 0; col < N; col++) {
        if (position(row, col)) {
            queen[row][col] = 1;
            mark = way(row + 1) || mark;
            queen[row][col] = 0;
        }
    }

    return mark;
}

int main()
{
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            queen[i][j]=0;
        }
    }
    if(way(0)==0){
        printf("have no answer.");
    }
    printf("%d",number);
    return 0;
}