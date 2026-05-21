
#include <stdio.h>
#include <string.h>
     void fun (char *ss)
     {
         char *temp = ss;
         int len = strlen(ss);
         for (int i = 0; i < len; i++){
             if(i % 2 == 1){
                 if(*temp >= 'a' && *temp <= 'z'){
                     *temp -= 32;
                 }
             }
             temp++;
         }
     }


int main()
{
    char tt[81];
    printf("\n Please enter an string within 80 characters:\n");
    gets(tt);

    printf("\n\nAfter changing, the string\n %s\n", tt);
    fun(tt);
    printf("\nbecomes \n %s\n", tt);

    return 0;
}