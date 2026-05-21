#include<stdio.h>
#include<string.h>
int main() 
{
    char num1[1000];
    char num2[1000];
    int x=1;
    scanf("%s",&num1);
    int n=strlen(num1);
    num2[0]=num1[0];
    for(int i=0;i<n;i++){
        if(num1[i]!=num1[i+1]){
            num2[x]=num1[i+1];
            x++;
        }
    }
    printf("%s",num2);
    return 0;
}