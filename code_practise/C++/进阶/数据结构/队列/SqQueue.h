#pragma once
#include<iostream>
#define Max 1024
using namespace std;
typedef struct 
{
    int data[Max];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue *&q)
{
    q=(SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = -1;
}

void DestroyQueue(SqQueue *&q)
{
    free(q);
}

bool IsEmpty(SqQueue *q)
{
    return(q->front == q->rear);
}

bool EnterQueue(SqQueue *&q, int e)
{
    if(q->rear == Max - 1)
    {
        return false;
    }
    else
    {
        q->data[++(q->rear)] = e;
        return true;
    }
}

bool OutQueue(SqQueue *&q, int &e)
{
    if(q->front==q->rear)
    {
        return false;
    }
    else
    {
        e = q->data[++q->front];
        return true;
    }
}