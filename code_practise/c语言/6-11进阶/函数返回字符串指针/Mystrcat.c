#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 80

char *Mystrcat(char *first, char *second);
int main()
{
    char F[2*N];
    char S[N];
    printf("Input the first string.");
    fgets(F, sizeof(F), stdin);
    printf("Input the second string.");
    fgets(S, sizeof(S), stdin);
    if (F[strlen(F) - 1] == '\n') {
        F[strlen(F) - 1] = '\0';
    }
    if (S[strlen(S) - 1] == '\n') {
        S[strlen(S) - 1] = '\0';
    }
    //可以改为S[strcspn(S,"\n")]=0;
    printf("The result is: %s\n",Mystrcat(F,S));
    system("PAUSE");
    return 0;
}

char *Mystrcat(char *first, char *second)
{
    char *Pstr=first;               //记录第一个字符串的起始指针
    while(*first!='\0'){
        first++;
    }
    for(;*second!='\0';first++,second++){
        *first=*second;
    }
    *first='\0';
    return Pstr;                    //返回记录的起始指针
}