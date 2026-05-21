#include<stdio.h>
#include<string.h>
int main()
{
    int n;
    printf("请输入个数：\n");
    scanf("%d",&n);

    char str[n][50];
    int num[n];
    const char keywords[][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    int find=0;

    for(int i=0; i<n; i++){
        printf("%d ",i+1);
        scanf("%s",str[i]);
        num[i]=strlen(str[i]);
    }
    printf("\n");

    for(int i=0; i<n; i++){
        for(int j=0; j<num[i]; j++){
            if(65<=(int)str[i][j] && (int)str[i][j]<=90 || 97<=(int)str[i][j] && (int)str[i][j]<=122 || 48<=(int)str[i][j] && (int)str[i][j]<=57 ||(int)str[i][j]==95){
                find=1;
                if((int)str[i][0]<=57 && (int)str[i][0]>=48){
                    find = 0;
                }
            }else{
                find=0;
                break;
            }
        }
        for(int k=0; k<numKeywords; k++){
            if(strcmp(str[i], keywords[k])== 0){
                find = 0;
                break;
            }
        }
        if(find==1){
            printf("%d   yes.\n", i+1);
        }else{
            printf("%d   no.\n", i+1);
        }
    }
    return 0;
}
// 大写字母A - Z的编码值范围是65 - 90。例如，A的 ASCII 码是65，B是66，以此类推，Z是90。
// 小写字母a - z的编码值范围是97 - 122。比如，a的 ASCII 码是97，b是98，一直到z是122。
// 数字：数字0 - 9的 ASCII 码值范围是48 - 57。其中0的 ASCII 码是48，1是49，依此类推，9是57。
// 下划线：下划线_的 ASCII 码是95。