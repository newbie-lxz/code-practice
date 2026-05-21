#include"MapStack.h"

#define N 10

void CreateMap(int map[N][N])
{
    
    int tempmap[N][N]=
    {
        {1,1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},
        {1,0,0,1,0,0,0,1,0,1},{1,0,0,0,0,1,1,0,0,1},
        {1,0,1,1,1,0,0,0,0,1},{1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,1},{1,0,1,1,1,0,1,1,0,1},
        {1,1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1}
    };
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            map[i][j]=tempmap[i][j];
        }
    }
} 

bool mappath(int xi,int yi,int xe,int ye)
{
    int mg[N][N];
    CreateMap(mg);
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            cout<<mg[i][j]<<"   ";
        }
        cout<<"\n"<<endl;
    }

    Box path[MAX],e;
    int i, j, il, jl, k, di;
    bool find;
    SqStack_box *st;
    InitStack(st);
    e.i = xi;
    e.j = yi;
    e.di = -1;
    PushStack(st,e);
    mg[xi][yi] = -1;
    while(!IsStackEmpty(st))
    {
        GetTop(st,e);
        i = e.i;
        j = e.j;
        di = e.di;
        if(i == xe&&j == ye)
        {
            cout<<"一条迷宫路径如下:\n"<<endl;
            k = 0;
            while(!IsStackEmpty(st))
            {
                PopStack(st,e);
                path[k++] = e;
            }
            while(k>=1)
            {
                k--;
                cout<<"\t("<<path[k].i<<","<<path[k].j<<")";
                if((k+2)%5==0)
                {
                    cout<<endl;
                }
            }
            cout<<endl;
            DestroyStack(st);
            return true;
        }
        find = false;
        while(di<4&&!find)
        {
            di++;
            switch(di)
            {
                case 0: 
                    il = i-1; 
                    jl = j;
                    break;
                case 1:
                    il = i;
                    jl = j+1;
                    break;
                case 2:
                    il = i+1;
                    jl = j;
                    break;
                case 3:
                    il = i;
                    jl = j-1;
                    break;
            }
            if(mg[il][jl]==0)
            {
                find = true;
            }
        }
        if(find)
        {
            st->data[st->top].di = di;
            e.i = il;
            e.j = jl;
            e.di = -1;
            PushStack(st,e);
            mg[e.i][e.j] = -1;
        }
        else
        {
            PopStack(st,e);
            mg[e.i][e.j] = 0;
        }
    }
    DestroyStack(st);
    return false;
}

int main()
{
    if(!mappath(1,1,8,8))
    {
        cout<<"无解"<<endl;
    }
    return 1;
}