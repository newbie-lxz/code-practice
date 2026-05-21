#include<stdlib.h>
#include<stdio.h>
typedef struct list{
    int data;
    struct list *pNext;
}node;
typedef node* link;

int main()
{
    int number;
    printf("请输入节点个数：");
    scanf("%d",&number);
    link head=NULL, tail=NULL;
    printf("请依次输入节点数据：\n");
    for(int i=0;i<number;i++){
        int a;
        scanf("%d",&a);
        link p=(link)malloc(sizeof(node));
        if(p==NULL){
            printf("no enough space.\n");
            exit(0);
        }
        p->data=a;
        p->pNext=NULL;
    
        if(head==NULL){
            head = p;
            tail = p;
        }else{
            tail->pNext=p;
            tail=p;
        }
    }
    for(int i=1;i<=number;i++){
        link first=head;
        link second=head;
        for(int j=0;j<i;j++){
            first=first->pNext;
        }
        while(first!=NULL){
            first = first->pNext;
            second = second->pNext;
        }
        printf("倒数第%d个节点的数据是==>%d\n",i,second->data);
    }

    link temp;
    while(head!=NULL){
        temp=head;
        head=head->pNext;
        free(temp);
    }
    return 0;
}