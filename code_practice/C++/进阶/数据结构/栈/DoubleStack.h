#ifndef DOUBLESTACK_H
#define DOUBLESTACK_H
#include<iostream>
using namespace std;
#define MAX 1024

typedef struct 
{
    double data[MAX];
    int top;
}SqStack_double;

void InitStack(SqStack_double*& s)
{
    s = (SqStack_double*)malloc(sizeof(SqStack_double));
    s->top = -1;
}

void DestroyStack(SqStack_double*& s)
{
    free(s);
    s = NULL;
}

bool IsStackEmpty(SqStack_double *s)
{
    return(s->top == -1);
}

bool PushStack(SqStack_double*& s, double e)
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

bool PopStack(SqStack_double*& s, double& e)
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

bool GetTop(SqStack_double* s, double& e)
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

#endif