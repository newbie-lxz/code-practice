#include<iostream>
using namespace std;
int main()
{
    int a=12;
    int b=10;
    int c = a & b;
    cout << c << endl; 
    /*
        a的二进制为1100
        b的二进制为1010
        &(按位与)同1为1，否则为0
        c的二进制为1000，是8
    */

    c = a | b;
    cout << c << endl;
    /*
        |(按位或)，有1则1，同0为0；
        c的二进制为1110，是14
    */ 

    c = ~a;
    cout << c << endl; 
    /*
        ~(按位取反)，1变成0，0变成1；
        c的二进制为1111 0011，是-13
    */

    c = a ^ b;
    cout << c << endl; 
    /*
        ^(按位异或)，不同为1，相同为0；
        c的二进制为0110，是6
    */
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << a <<" "<< b <<endl;
    /*交换两个变量的值
     a ^ 0 = a;
     a ^ a = 0;.
     a ^ b ^ a = b;
    */
    return 0;
}