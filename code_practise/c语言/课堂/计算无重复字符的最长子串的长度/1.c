#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void MAX(char *str);
int main()
{
    char str[1000];
    scanf("%s",str);
    MAX(str);
    return 0;
}

void MAX(char *str){
    int right=0;
    int left=0;
    int max=0;
    int now=0;
    int len = strlen(str);
    int *ASC=(int *)malloc(128*sizeof(int));            //把ASCII码初始化
    for(int i=0;i<128;i++){
        ASC[i]=-1;
    }

    while(right<len){
        if(ASC[str[right]]!=-1 && ASC[str[right]]>=left){
            left = ASC[str[right]]+1;                   //遇到重复字符，移动左边界
        }
        ASC[str[right]]=right;                          
        now = right-left+1;                             //目前的长度
        if(now>max){
            max=now;
        }
        right++;
    }

    free(ASC);
    printf("%d",max);
}
