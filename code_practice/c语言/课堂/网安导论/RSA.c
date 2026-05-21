#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define e 17
int randomnumber(int min,int max);
int is_prime(int num);
int extend_gcd(int a, int b, int *x, int *y);
int main()
{
    srand(time(NULL));
    int min = 1<<14;
    int max = (1<<16)-1;
    int p = randomnumber(min,max);
    int q = randomnumber(min,max);
    while(q==p||(p-1)*(q-1)%e==0){
        q = is_prime(randomnumber(min,max));
    }
    int Euler_totient_function = (p-1)*(q-1);
     
    int x, y;
    int d = extend_gcd(e, Euler_totient_function, &x, &y);
    if (d == -1) {
        return 0;
    } else {
        d = (x % Euler_totient_function + Euler_totient_function) % Euler_totient_function;
    }
    return 0;
}

int randomnumber(min,max){
    int prime=0;
    do{
        prime=min+rand()%(max-min+1);
    }while(is_prime(prime)==0);
    return prime;
}//生成随机素数

int is_prime(num){
    if (num % 2 == 0 || num % 3 == 0) return 0;
    int i = 5;
    while (i * i <= num) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
        i += 6;
    }
    return 1;
}//判断是否是素数

int extend_gcd(int a, int b, int *x, int *y) {
    int x1, y1;
    int gcd = extend_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}