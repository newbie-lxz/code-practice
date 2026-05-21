#pragma once
#include<iostream>
#define Max 1024
using namespace std;
//队满MAX
typedef struct 
{
    int data[Max];
    int front, count;
}SqCircleQueuemax;

void InitQueue(SqCircleQueuemax *&q)
{
    q=(SqCircleQueuemax *)malloc(sizeof(SqCircleQueuemax));
    q->front = q->count = 0;
}

void DestroyQueue(SqCircleQueuemax *&q)
{
    free(q);
}

bool IsEmpty(SqCircleQueuemax *q)
{
    return(q->count == 0);
}

bool EnterQueue(SqCircleQueuemax *&q, int e)
{
    int rear;
    if(q->count == Max)
    {
        return false;
    }
    else
    {
        rear = (q->front + q->count)%Max;
        rear = (rear + 1)%Max;
        q->data[rear] = e;
        q->count++;
        return true;
    }
}

bool OutQueue(SqCircleQueuemax *&q, int &e)
{
    if(q->count == 0)
    {
        return false;
    }
    else
    {
        q->front = (q->front+1)%Max;
        e = q->data[q->front];
        q->count--;
        return true;
    }
}