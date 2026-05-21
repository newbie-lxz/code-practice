#ifndef INTSTACK_H
#define INTSTACK_H
#include<iostream>
using namespace std;
#define MAX 1024

typedef struct 
{
    int data[MAX];
    int top;
}SqStack_int;

void InitStack(SqStack_int*& s)
{
    s = (SqStack_int*)malloc(sizeof(SqStack_int));
    s->top = -1;
}

void DestroyStack(SqStack_int*& s)
{
    free(s);
    s = NULL;
}

bool IsStackEmpty(SqStack_int *s)
{
    return(s->top == -1);
}

bool PushStack(SqStack_int*& s, int e)
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

bool PopStack(SqStack_int*& s, int& e)
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

bool GetTop(SqStack_int* s, int& e)
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