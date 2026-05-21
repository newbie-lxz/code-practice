#include<stdio.h>
#include<string.h>
int main()
{
    printf("请输入两个全部由小写字母组成的字符串。\n");
    char str1[1000];
    char str2[1000];
    scanf("%s",&str1);
    scanf("%s",&str2);
    int n1=strlen(str1);
    int n2=strlen(str2);
    int find = 0;
    if(n1==n2){
        find = 1;
        for(int i=0; i<n1-1; i++){
            for(int j=i+1; j<n1; j++){
                if(str1[i]==str1[j]){
                    if(str2[i]!=str2[j]){
                        goto here;
                    }
                }
            }
        }
    }
    here:
    if(find==1){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return 0;
}