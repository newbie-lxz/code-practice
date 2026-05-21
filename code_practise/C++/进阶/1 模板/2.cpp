#include<iostream>
using namespace std;

template<typename T>
void swapAll(T &a, T &b)   
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void orderAll(T arr[], int len)
{
    for(int i = 0; i < len-1; i++)
    {
        int temp = i;
        for(int j = i+1; j < len; j++)
        {
            if(arr[temp] < arr[j])
            {
                temp = j;
            }
        }
        swapAll(arr[i], arr[temp]);
    }
}

template<typename T>
void printAll(T arr[], int len)    
{
    for(int i = 0; i < len; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

template<typename T>
void test(T *arr, int len)
{
    orderAll(arr, len);
    printAll(arr, len);
}

int main()
{
    char arr[] = "wdnmd";
    int charlen = sizeof(arr) / sizeof(char);
    test(arr, charlen);

    int Arr[] = {1,1,4,5,1,4};
    int intlen = sizeof(Arr) / sizeof(int);
    test(Arr, intlen);
    return 0;
}