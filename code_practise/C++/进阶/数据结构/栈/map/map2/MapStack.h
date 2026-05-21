#ifndef MAPSTACK_H
#define MAPSTACK_H
#include<iostream>
using namespace std;
#define MAX 1024

typedef struct 
{
    int i;
    int j;
    int di;
}Box;

typedef struct 
{
    Box data[MAX];
    int top;
}SqStack_box;

void InitStack(SqStack_box*& s)
{
    s = (SqStack_box*)malloc(sizeof(SqStack_box));
    s->top = -1;
}

void DestroyStack(SqStack_box*& s)
{
    free(s);
    s = NULL;
}

bool IsStackEmpty(SqStack_box *s)
{
    return(s->top == -1);
}

bool PushStack(SqStack_box*& s, Box e)
{
    if(s->top < MAX-1)
    {
        s->data[++(s->top)] = e;
        return true;
    }
    else{ 
        return false;
    }
}

bool PopStack(SqStack_box*& s, Box& e)
{
    if(s->top == -1)
    {
        return false;
    }
    else{
        e = s->data[s->top--];
        return true;
    }
}

bool GetTop(SqStack_box* s, Box& e)
{
    if(s->top == -1)
    {
        return false;
    }
    else{
        e = s->data[s->top];
        return true;
    }
}

bool IsExist(SqStack_box* s, Box e)
{
    for(int k = s->top;k>=0;k--)
    {
        if(s->data[k].i==e.i&&s->data[k].j==e.j)
        {
            return false;
        }
    }
    return true;
}

#endif