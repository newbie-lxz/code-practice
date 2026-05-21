#pragma once
#include<iostream>
using namespace std;

typedef struct qnode
{
    int data;
    struct qnode *next;
}DataNode;



void InitQuene(DataNode *&rear)
{
    rear = NULL;
}

void DestroyQuene(DataNode *&rear) {
    if (rear == NULL) {
        return; // 队列为空，无需销毁
    }

    DataNode *current = rear->next; // 从队列头节点开始
    while (current != rear) { // 遍历直到回到尾节点
        DataNode *temp = current;
        current = current->next; // 移动到下一个节点
        free(temp); // 释放当前节点
    }

    // 释放尾节点本身
    free(rear);
    rear = NULL; // 将尾指针置为NULL，表示队列已销毁
}

bool IsEmpty(DataNode *rear)
{
    return(rear == NULL);
}

void EnterQuene(DataNode *&rear, int e)
{
    DataNode *p;
    p = (DataNode *)malloc(sizeof(DataNode));
    p->data = e;
    if(rear == NULL)
    {
        p->next = p;
        rear = p;
    }
    else
    {
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
}

bool OutQuene(DataNode *&rear, int &e)
{
    DataNode *p;
    if(rear == NULL)
    {
        return false;
    }
    else if(rear->next = rear)
    {
        e = rear->data;
        free(rear);
        rear = NULL;
    }
    else 
    {
        p = rear ->next;
        e = p->data;
        rear->next = p->next;
        free(p);
    }
    return true;
}