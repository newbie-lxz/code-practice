#pragma once
#include<iostream>
#define Max 1024
using namespace std;
//队满MAX-1
typedef struct 
{
    int data[Max];
    int front, rear;
}SqCircleQueue;

void InitQueue(SqCircleQueue *&q)
{
    q=(SqCircleQueue *)malloc(sizeof(SqCircleQueue));
    q->front = q->rear = 0;
}

void DestroyQueue(SqCircleQueue *&q)
{
    free(q);
}

bool IsEmpty(SqCircleQueue *q)
{
    return(q->front == q->rear);
}

bool EnterQueue(SqCircleQueue *&q, int e)
{
    if((q->rear+1)%Max == q->front)
    {
        return false;
    }
    else
    {
        q->rear = (q->rear+1)%Max;
        q->data[q->rear] = e;
        return true;
    }
}

bool OutQueue(SqCircleQueue *&q, int &e)
{
    if(q->front==q->rear)
    {
        return false;
    }
    else
    {
        q->front = (q->front+1)%Max;
        e = q->data[q->front];
        return true;
    }
}