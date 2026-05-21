#include<stdio.h>
#include<stdlib.h>
#define N 80
int main()
{
    FILE *fp;
    char str[N];
    if((fp=fopen("demo.txt","a"))==NULL){
        printf("Failure to open demo.txt!\n");
        exit(0);
    }
    gets(str);
    fputs(str,fp);
    fclose(fp);
    if((fp=fopen("demo.txt","r"))==NULL){
        printf("Failure to open demo.txt!\n");
        exit(0);
    }
    fgets(str,N,fp);
    puts(str);
    fclose(fp);
    return 0;
}