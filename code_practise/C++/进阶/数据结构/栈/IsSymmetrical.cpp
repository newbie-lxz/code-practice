#include<string>
#include"charstack.h"

bool IsSymmetrical(char str[])
{
    SqStack_char* s;
    InitStack(s);
    int i = 0;
    char e;
    while(str[i] != '\0')
    {
        PushStack(s,str[i++]);
    }
    for(i=0; str[i] != '\0'; i++)
    {
        PopStack(s,e);
        if(str[i]!=e)
        {
            DestroyStack(s);
            return false;
        }
    }
    DestroyStack(s);
    return true;
}

int main()
{
    char str[MAX];
    cin.getline(str,MAX);
    cout<<IsSymmetrical(str)<<endl;
    return 0;
}