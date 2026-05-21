#include"swap.h"
void swap(int a, int b){
    int mid = a;
    a = b;
    b = mid;

    cout << a << endl;
    cout << b << endl;
}