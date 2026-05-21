#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50

typedef char SqBinTree[MaxSize];

typedef struct node {
    char data;
    struct node *lchild;
    struct node *rchild;
} BTNode;

typedef struct {
    BTNode* data[MaxSize];
    int front;
    int rear;
} Queue;

void InitQueue(Queue* q) {
    q->front = q->rear = 0;
}

int IsEmpty(Queue* q) {
    return q->front == q->rear;
}

void EnQueue(Queue* q, BTNode* node) {
    if (q->rear < MaxSize - 1) {
        q->data[q->rear++] = node;
    }
}

BTNode* DeQueue(Queue* q) {
    if (!IsEmpty(q)) {
        return q->data[q->front++];
    }
    return NULL;
}

void ConvertToSeqStorage(BTNode* root, SqBinTree a) {
    if (root == NULL) {
        return;
    }
    Queue q;
    InitQueue(&q);
    EnQueue(&q, root);
    int index = 0;

    while (!IsEmpty(&q)) {
        BTNode* current = DeQueue(&q);
        while(index<MaxSize && a[index]=='#')
            {
                int i = 2*index+1;
                if(i < MaxSize)
                {
                    a[i] = '#';
                    if(i+1<MaxSize)
                    {
                        a[i+1] = '#';
                    }
                }
                index++;
            }
        if (current != NULL) {
            if(index<MaxSize)
            {
                a[index++] = current->data;
                EnQueue(&q, current->lchild); 
                EnQueue(&q, current->rchild);
            }
        } else {
            while(index<MaxSize && a[index]=='#')
            {
                int i = 2*index+1;
                if(i < MaxSize)
                {
                    a[i] = '#';
                    if(i+1<MaxSize)
                    {
                        a[i+1] = '#';
                    }
                }
                index++;
            }
            if(index<MaxSize)
            {
                int i = 2*index+1;
                if(i < MaxSize)
                {
                    a[i] = '#';
                    if(i+1<MaxSize)
                    {
                        a[i+1] = '#';
                    }
                }
                a[index++] = '#';
            }
        }
    }
}

void PrintSeqStorage(SqBinTree a) {
    for (int i = 0; i < MaxSize; i++) {
        printf("%c ", a[i]);
    }
    printf("\n");
}


BTNode* CreateBTNode(char data, BTNode* lchild, BTNode* rchild) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->data = data;
    node->lchild = lchild;
    node->rchild = rchild;
    return node;
}

int main() {
    BTNode* root = CreateBTNode('A',
                                CreateBTNode('B', CreateBTNode('D', NULL,CreateBTNode('F',CreateBTNode('G', NULL, NULL),NULL)), NULL),
                                CreateBTNode('C', NULL, CreateBTNode('E', NULL, NULL)));

    SqBinTree a;
    ConvertToSeqStorage(root, a);
    PrintSeqStorage(a);

    return 0;
}