#ifndef CHARSTACK_H
#define CHARSTACK_H
#include<iostream>
using namespace std;
#define MAX 1024

typedef struct 
{
    char data[MAX];
    int top;
}SqStack_char;

void InitStack(SqStack_char*& s)
{
    s = (SqStack_char*)malloc(sizeof(SqStack_char));
    s->top = -1;
}

void DestroyStack(SqStack_char*& s)
{
    free(s);
    s = NULL;
}

bool IsStackEmpty(SqStack_char *s)
{
    return(s->top == -1);
}

bool PushStack(SqStack_char*& s, char e)
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

bool PopStack(SqStack_char*& s, char& e)
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

bool GetTop(SqStack_char* s, char& e)
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