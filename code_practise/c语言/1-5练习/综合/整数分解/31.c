#include<stdio.h>
int main()
{
  int n=0;
  int t;
  printf("请输入一个数字：");
  scanf("%d", &n);
  t=n;
  int digit = 0;
  do{
    n/=10;
    if(n>0){
      digit++;
    }else{
      break;
    }
  }while(n>0);
  
  int x=1;
  int y=0;
  for(y=0;y<digit;y++){
      x*=10;
  }
  
  printf("%d\n", x);

  do{
    int d = t / x;
    printf("%d", d);
    if(x>9){
      printf(" ");
    }
    t %= x;
    x /= 10;
  }while(x>0);
  return 0;
}