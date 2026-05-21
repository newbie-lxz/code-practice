#ifndef LinkStack_H
#define LinkStack_H
#include<iostream>
using namespace std;
#define MAX 1024

typedef struct linkstack
{
    char data;
    struct linkstack *next;
}LinkStack;

void InitStack(LinkStack*& s)
{
    s = (LinkStack*)malloc(sizeof(LinkStack));
    s->next = NULL;
}

void DestroyStack(LinkStack*& s)  
{
    LinkStack *pre = s, *p = s->next;
    while(p != NULL)
    {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
    s = NULL;
}

bool IsStackEmpty(LinkStack *s)
{
    return(s->next == NULL);
}

void PushStack(LinkStack*& s, char e)
{
    LinkStack *p = (LinkStack*)malloc(sizeof(LinkStack));
    p->data = e;
    p->next = s->next;
    s->next = p; 
}

bool PopStack(LinkStack*& s, char& e)
{
    LinkStack *p;
    if(s->next == NULL)
    {
        return false;
    }
    p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    p = NULL;
    return true;
}

bool GetTop(LinkStack* s, char& e)
{
    if(s->next == NULL)
    {
        return false;
    }
    e = s->next->data;
    return true;
}

#endif 