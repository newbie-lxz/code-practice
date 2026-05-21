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

int main()
{
    int i,j;
    int map[N][N];
    CreateMap(map);
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            cout<<map[i][j]<<"   ";
        }
        cout<<"\n"<<endl;
    }

    SqStack_box *Mapstack;
    InitStack(Mapstack);
    Box e;
    e.i = 1;
    e.j = 1;
    e.di = -1;
    PushStack(Mapstack,e);
    while(!(e.i==N-2&&e.j==N-2))
    {
        i = e.i;
        j = e.j;
        while(1)
        {
            e.di++;
            switch(e.di)
            {
                case 0:
                    e.i = i-1;
                    e.j = j;
                    break;
                case 1:
                    e.j = j+1;
                    e.i = i;
                    break;
                case 2:
                    e.i = i+1;
                    e.j = j;
                    break;
                default:
                    e.i = i;
                    e.j = j-1;
                    break;
            }
            if(e.di>3)
            {
                PopStack(Mapstack);
                GetTop(Mapstack,e);
                break;
            }
            if(map[e.i][e.j]==0 && IsExist(Mapstack,e))
            {
                Box temp;
                GetTop(Mapstack,temp);
                PopStack(Mapstack);
                temp.di = e.di;
                PushStack(Mapstack,temp);
                e.di = -1;
                PushStack(Mapstack,e);
                break;
            }
        }
    }
    for(int k=0; k<=Mapstack->top;k++)
    {
        cout<<"("<<Mapstack->data[k].i<<","<<Mapstack->data[k].j<<")\t";
        if((k+1)%5==0)
        {
            cout<<endl;
        }
    }
    DestroyStack(Mapstack);
    return 0;
}