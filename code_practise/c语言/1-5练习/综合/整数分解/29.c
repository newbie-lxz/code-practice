#include<stdio.h>
int main()
{
  int x;
  scanf("%d", &x);
  int n=0;
  int i=0;
  int y=0;

  for(x>0; n=x%10; x/=10 ){
    i=i*10+n;
  }
  
  do{
        y=i%10;
        i /= 10;
        if(i>0){
        printf("%d ", y);
        }else {
        printf("%d", y);
        }
    }while(i>0);
  return 0;
}