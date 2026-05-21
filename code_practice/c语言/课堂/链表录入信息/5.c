#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct link {
    char number[15];
    int score[3];
    char name[50];
    float aver;
    struct link* next;
} Link;

Link *Add_information(Link *head);                  // 添加学生信息
Link *Change_information(Link *head);               // 改动学生信息
Link *Delete_information(Link *head);               // 删除学生信息
void IDfind(Link *head);                           // 通过学号找学生
void namefind(Link *head);                          // 通过名字找学生
void Print(Link *head);                             // 打印链表
void Delete(Link *head); 
void Scoreorder(Link *head);                           // 清空链表

int main()
{
    int code;
    Link *head = NULL;
    do {
        scanf("%d", &code);
        scanf("%*c");
        switch (code) {
            case 1:
                head = Add_information(head);             //添加信息
                break;
            case 2:
                head = Change_information(head);          //改动信息
                break;
            case 3:
                head = Delete_information(head);          //删除信息
                break;
            case 4:
                IDfind(head);                           //查找学号
                break;
            case 5:
                namefind(head);                         //查找名字
                break;
            case 6:
                Print(head);                            //学号顺序
                break;
            case 7:
                Scoreorder(head);                    //总分顺序
                break;
            default:
                break;
        }
    } while (code!= 0);
    Delete(head);
    return 0;
}

Link *Add_information(Link *head) {
    Link *pr = head, *newNode, *prev = NULL;
    newNode = (Link *)malloc(sizeof(Link));
    if (newNode == NULL) {
        printf("No enough space!\n");
        exit(0);
    }
    scanf("%s", newNode->number);
    scanf("%*c");
    scanf("%d %d %d", &newNode->score[0], &newNode->score[1], &newNode->score[2]);
    newNode->aver = (float)(newNode->score[0] + newNode->score[1] + newNode->score[2]) / 3;
    scanf("%*c");
    fgets(newNode->name, sizeof(newNode->name), stdin);
    if (newNode->name[strlen(newNode->name) - 1] == '\n') {
        newNode->name[strlen(newNode->name) - 1] = '\0';
    }
    newNode->next = NULL;

    // 检查链表是否为空
    if (head == NULL) {
        head = newNode;
    } else {
        while (pr != NULL && strcmp(pr->number, newNode->number) < 0) {
            prev = pr;
            pr = pr->next;
        }
        if (pr != NULL && strcmp(pr->number, newNode->number) == 0) {
            // 更新现有节点的内容
            pr->aver = newNode->aver;
            memcpy(pr->score, newNode->score, sizeof(newNode->score));
            strcpy(pr->name, newNode->name);
            free(newNode);
        } else {
            if (prev == NULL) {
                newNode->next = head;
                head = newNode;
            } else {
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
    }
    return head;
}

void Scoreorder(Link *head) {
    Link *newhead = NULL, *node=NULL, *pr = head;
    // 复制链表内容到newhead，并在复制的同时按照平均分进行插入排序
    while (pr != NULL) {
        node = (Link*)malloc(sizeof(Link));
        if (node == NULL) {
            printf("No enough space!\n");
            exit(0);
        }
        strcpy(node->number, pr->number);
        for (int i = 0; i < 3; i++) {
            node->score[i] = pr->score[i];
        }
        strcpy(node->name, pr->name);
        node->aver = pr->aver;
        node->next = NULL;

        // 插入新节点到newhead，保持平均分顺序
        if (newhead == NULL || newhead->aver < node->aver) {
            node->next = newhead;
            newhead = node;
        } else {
            Link *temp = newhead;
            while (temp->next != NULL && temp->next->aver >= node->aver) {
                temp = temp->next;
            }
            node->next = temp->next;
            temp->next = node;
        }
        pr = pr->next;
    }
    Print(newhead);
    Delete(newhead);
}

Link *Change_information(Link *head) {
    Link *pr = head;
    char newnumber[15];
    scanf("%s", newnumber);
    do {
        if (strcmp(pr->number, newnumber) == 0) {
            scanf("%d %d %d", &pr->score[0], &pr->score[1], &pr->score[2]);
            pr->aver = (float)(pr->score[0] + pr->score[1] + pr->score[2]) / 3;
            scanf("%*c");
            fgets(pr->name, sizeof(pr->name), stdin);
            if (pr->name[strlen(pr->name) - 1] == '\n') {
                pr->name[strlen(pr->name) - 1] = '\0';
            }
            break;
        }
        pr = pr->next;
    } while (pr&&strcmp(pr->number, newnumber) <= 0);
    if (pr == NULL || strcmp(pr->number, newnumber) > 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // 清除输入缓冲区直到换行符或文件末尾
    }
    return head;
}

Link *Delete_information(Link *head) {
    Link *p = NULL, *pr = head;
    char newnumber[15];
    scanf("%s", newnumber);
    if (head != NULL && strcmp(head->number, newnumber) == 0) {
        p = head;
        head = head->next;
        free(p);
    } else {
        while (pr->next != NULL && strcmp(pr->next->number, newnumber)<0) {
            pr = pr->next;
        }
        if (pr->next != NULL && strcmp(pr->next->number, newnumber) == 0) {
            p = pr->next;
            pr->next = p->next;
            free(p);
        }
    }
    return head;
}

void IDfind(Link *head) {
    Link *pr = head;
    char newnumber[15];
    scanf("%s", newnumber);
    while (pr&&pr->number<=newnumber) {
        if (strcmp(pr->number, newnumber) == 0) {
            printf("%s %s %d %d %d \n", pr->number, pr->name, pr->score[0], pr->score[1], pr->score[2]);
            break;
        }
        pr = pr->next;
    }
}

void namefind(Link *head) {
    Link *pr = head;
    char newname[50];
    fgets(newname, sizeof(newname), stdin);
    if (newname[strlen(newname) - 1] == '\n') {
        newname[strlen(newname) - 1] = '\0';
    }
    while (pr) {
        if (strcmp(pr->name, newname) == 0) {
            printf("%s %s %d %d %d \n", pr->number, pr->name, pr->score[0], pr->score[1], pr->score[2]);
        }
        pr = pr->next;
    }
}

void Print(Link *head) {
    Link *pr = head;
    while (pr) {
        printf("%s %s %d %d %d\n", pr->number, pr->name, pr->score[0], pr->score[1], pr->score[2]);
        pr = pr->next;
    }
}

void Delete(Link *head) {
    Link *pr = head, *p = NULL;
    while (pr) {
        p = pr;
        pr = pr->next;
        free(p);
    }
}
