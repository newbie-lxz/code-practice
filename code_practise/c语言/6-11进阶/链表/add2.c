#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int value;
    struct node *next;
 }Node;

typedef struct list{
    Node *head;         //头指针
    Node *tail;         //尾指针
 }List;

void add(List *pList, int number);

int main(int argc, char const *argv[]){
    List list;
    int number;
    list.head=list.tail=NULL;
    do{
        scanf("%d",&number);
        if(number != -1){
            add(&list,number);
        }
    }while (number!=-1);
    return 0;
 }

void add(List *pList, int number){
    Node *p=(Node*)malloc(sizeof(Node));
    if(p==NULL){
        printf("no enough space.\n");
        exit(0);
    }
    p->value = number;
    p->next = NULL;
    // Node *last = pList->head;
    // if(last){
    //     while(last->next){
    //         last = last->next;
    //     }
    //     last -> next = p;
    // }else{
    //     pList->head=p;
    //     pList->tail=p;
    // }
    if (pList->head == NULL) {
        // 链表为空时，头指针和尾指针都指向新节点
        pList->head = p;
        pList->tail = p;
    } else {
        // 链表不为空时，将新节点添加到尾节点后面，并更新尾指针
        pList->tail->next = p;
        pList->tail = p;
    }
}