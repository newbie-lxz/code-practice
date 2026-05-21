 #include <stdio.h> 
#include<string.h>

 void order(const char* str[], int n) ;

 int main() 
 { 
 const char *str[] = { "a", "abc", "ab", "abcde", "abcd" }; 
 order(str, 5); 
 for (int i = 0; i < 5; i++) 
 { 
 printf("%s\n", str[i]); 
 } 
return 0;
 } 

 void order(const char* str[], int n) 
 { 
 for (int i = 0; i < n; i++) 
 { 
 for (int j = i + 1; j < n; j++) 
{ 
if (strlen(str[i]) < strlen(str[j])) 
 { 
 const char * p = str[j]; 
 str[j] = str[i]; 
 str[i] = p; 
 } 
 } 
} 
 } 