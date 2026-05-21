#include<stdio.h>
int main()
{
    int number, n;
    int inp;
    int finished=0;
    int cnt=0;
    scanf("%d %d", &number,&n);
    do{
        scanf("%d", &inp);
        cnt++;
        if(inp<=0||cnt>n){
        printf("Game Over\n");
        finished=1;
        break;
        }else if(inp<number){
            printf("Too small\n");
        }else if(inp>number){
            printf("Too big\n");
        }else if("inp==number"){
            break;
        }
    }while(inp!=number);
    if(finished==0){
    if(cnt==1){
        printf("Bingo!\n");
    }else if(cnt<=3){
        printf("Lucky You\n");
    }else if(cnt<=n){
        printf("Good Guess\n");
    }
    }
    return 0;
}