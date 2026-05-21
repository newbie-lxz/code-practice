#include<iostream>
#include<ctime>
using namespace std;
int main()
{
    srand(time(0));
    int c = rand()%100+1;
    cout << c << endl;
    return 0; 
}