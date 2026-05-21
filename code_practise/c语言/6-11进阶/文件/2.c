#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    FILE *fp;
    char ch;
    int i;
    if ((fp=fopen("demo.bin","wb"))==NULL)
    {
        printf("Failure to open demo.bin!\n");
        exit(0);
    }
    for(i=0; i<128; i++){
        fputc(i,fp);
    }
    fclose(fp);
    if((fp=fopen("demo.bin","rb"))==NULL){
        printf("Failure to open demo.bin!\n");
        exit(0);
    }
    while((ch=fgetc(fp))!=EOF)
    {
        if(isprint(ch))
            printf("%c\t",ch);
        else
            printf("%d\t",ch);
    }
    fclose(fp);
    system("PAUSE");
    return 0;
}