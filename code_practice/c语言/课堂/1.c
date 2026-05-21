#include<stdio.h>
char map[200][201];
int min = 40000;
int M,N;
int visit[200][200][2] = {0,0};

int In(int x, int y)
{
    return x>=0 && x<M && y>=0 && y<N;
}

void bfs(int x, int y, int T, int num)
{
    if(In(x,y) && num<min && (visit[x][y][0] > num+1 || visit[x][y][0] == 0 || T >= visit[x][y][1]))
    {
        if(map[x][y] == '+')
        {
            min = num;
            return;
        }
        else if(map[x][y] == '*' || map[x][y] == '#' || map[x][y] == '@' )
        {
            if(map[x][y] == '#'&& T<1)
            {
                return;
            }
            else if(map[x][y] == '#'&& T>=1)
            {
                T--;
            }
            num++;
            visit[x][y][0] = num;
            visit[x][y][1] = T;
            bfs(x+1,y,T,num);
            bfs(x-1,y,T,num);
            bfs(x,y+1,T,num);
            bfs(x,y-1,T,num);
        }
    }
    else 
        return;
}

int main()
{
    int T,num=0;
    scanf("%d %d %d",&M,&N,&T);
    for(int i=0; i<M; i++)
    {
        scanf("%s",map[i]);
    }
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map[i][j] == '@')
            {
                bfs(i,j,T,num);
                break;
            }
            
        }
    }
    if (min==40000)
        printf("-1");
    else
        printf("%d",min);
    return 0;
}