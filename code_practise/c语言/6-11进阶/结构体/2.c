#include <stdio.h> 
 
 int main() 
 { 
 int x[3][3] = { {1,2}, {3,4}, {5,6} }; 
 
 int *p1 = x; 
 int (*p2)[3] = x; 
 printf("%d\n", p1 == p2); 
 
 p1 += 2; 
 printf("%d\n", *p1); 
 
 p2++; 
 printf("%d\n%d\n", *p2, **p2); 
 p2++; 
 printf("%d\n", p1 == p2); 
 return 0; 
 } 
