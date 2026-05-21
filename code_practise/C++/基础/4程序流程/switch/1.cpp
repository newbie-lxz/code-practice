#include<iostream>
using namespace std;
int main()
{
    cout<<"请打分："<<endl;
    int a;
    cin>> a ;
    switch(a){
        case 10:
        case 9:
            cout<<"wonderful"<<endl;
            break;
        case 8:
        case 7:
            cout<<"gteat"<<endl;
            break;
        case 6:
        case 5:
            cout<<"just so so"<<endl;
            break;
        default:
            cout<<"terrible"<<endl;
            break;
    }
    return 0;
}