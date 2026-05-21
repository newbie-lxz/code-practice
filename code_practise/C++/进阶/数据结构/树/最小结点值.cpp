// 假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法，求二叉树 b中最小值的结点值。
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *lchild;
    struct node *rchild;
} BTNode;

char Min(BTNode *b) {
    if (b == NULL) {
        return '\0'; 
    }

    char minl = Min(b->lchild);
    char minr = Min(b->rchild); 

    if (minl == '\0') {
        minl = b->data;
    }

    if (minr == '\0') {
        minr = b->data;
    }

    char min = (minl < minr) ? minl : minr;
    return (b->data < min) ? b->data : min;
}


int main() {
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    root->data = 'C';
    root->lchild = (BTNode*)malloc(sizeof(BTNode));
    root->rchild = (BTNode*)malloc(sizeof(BTNode));
    root->lchild->data = 'A';
    root->lchild->lchild = NULL;
    root->lchild->rchild = NULL;
    root->rchild->data = 'B';
    root->rchild->lchild = (BTNode*)malloc(sizeof(BTNode));
    root->rchild->rchild = NULL;
    root->rchild->lchild->data = 'D';
    root->rchild->lchild->lchild = NULL;
    root->rchild->lchild->rchild = NULL;

    char minVal = Min(root);
    printf("二叉树中的最小值为：%c\n", minVal);

    return 0;
}