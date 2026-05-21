#include<stdio.h>
#include<string.h>

void Count_substring(char* t, char* w );
int main()
{
    char text[1000];
    char word[100];

    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';

    char* t = text;
    char* w = word;

    Count_substring(t,w);

    return 0;
}

void Count_substring(char* t, char* w){
    int n=0;
    int m=0;
    int len1=strlen(t);
    int len2=strlen(w);
    for(int i=0;i<len1;i++){
        for(int j=0;j<len2;j++){
            while (*(t + i) ==' ') {
                i++;
            }
            if(*(t+i)==*(w+j)||*(t+i)==*(w+j)-32){
                i++;
                m++;
            }else{
                break;
            }
        }
        if(m==len2){
            n++;
        }
        m=0;
    }
    printf("%d",n);
}