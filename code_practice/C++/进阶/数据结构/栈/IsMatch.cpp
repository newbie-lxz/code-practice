#include"LinkStack.h"

bool Parenthesis(char str[])
{
    LinkStack *s;
    InitStack(s);
    char e;
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '(')
        {
            PushStack(s, str[i]);
        } else if (str[i] == ')') 
        {
            if (IsStackEmpty(s)) 
            { 
                DestroyStack(s);
                return false;
            }
            PopStack(s, e); 
        }
    }
    if(IsStackEmpty)
    {
        DestroyStack(s);
        return true;
    }
    else
    {
        DestroyStack(s);
        return false;
    }
}

int main()
{
    char str[MAX];
    cin.getline(str,MAX);
    cout<<Parenthesis(str)<<endl;
    return 0;
}