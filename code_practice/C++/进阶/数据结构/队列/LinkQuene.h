#pragma once
#include<iostream>
using namespace std;

typedef struct qnode
{
    int data;
    struct qnode *next;
}DataNode;

typedef struct 
{
    DataNode *front;
    DataNode *rear;
}LinkQuene;

void InitQuene(LinkQuene *&q)
{
    q = (LinkQuene *)malloc(sizeof(LinkQuene));
    q->front = q->rear = NULL;
}

void DestroyQuene(LinkQuene *&q)
{
    DataNode *pre = q->front, *p;
    if(pre != NULL)
    {
        p = pre->next;
        while(p != NULL)
        {
            free(pre);
            pre = p; 
            p = p->next;
        }
        free(pre);
    } 
    free(q);
}

bool IsEmpty(LinkQuene *q)
{
    return(q->rear == NULL);
}

void EnterQuene(LinkQuene *&q, int e)
{
    DataNode *p;
    p = (DataNode *)malloc(sizeof(DataNode));
    p->data = e;
    p->next = NULL;
    if(q->rear == NULL)
    {
        q->front = p;
        q->rear = p;
    }
    else
    {
        q->rear->next = p;
        q->rear = p;
    }
}

bool OutQuene(LinkQuene *&q, int &e)
{
    DataNode *p;
    if(q->rear == NULL)
    {
        return false;
    }
    p = q->front;
    if(q->front == q->rear)
    {
        q->front = q->rear = NULL;
    }
    else
    {
        q->front = q->front->next;
    }
    e = p->data;
    free(p);
    return true;
}