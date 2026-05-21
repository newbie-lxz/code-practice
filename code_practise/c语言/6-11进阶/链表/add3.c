#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int value;
    struct node *next;
 }Node;

typedef struct list{
    Node *head;
 }List;

void add(List *pList, int number);
void print(List *pList);

int main(int argc, char const *argv[]){
    List list;
    int number;
    list.head=NULL;
    do{
        scanf("%d",&number);
        if(number != -1){
            add(&list,number);
        }
    }while (number!=-1);
    // Node *p;
    // for(p=list.head;p;p->next){
    //     printf("%d\t",p->value);
    // }
    // printf("\n");
    print(&list);
    scanf("%d",&number);
    Node *p;
    for(p=list.head;p;p=p->next){
        if(p->value==number){
            printf("find it!\n");
            break;
        }
    }
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
    Node *last = pList->head;
    if(last){
        while(last->next){
            last = last->next;
        }
        last -> next = p;
    }else{
        pList->head=p;
    }
}

void print(List *pList){
    Node *p;
    for(p=pList->head;p;p->next){
        printf("%d\t",p->value);
    }
    printf("\n");
}