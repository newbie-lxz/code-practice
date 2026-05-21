#include"CharStack.h"
#include"DoubleStack.h"
void trans(char postexp[], char *exp)
{
    char e;
    int i=0,j=0;
    SqStack_char *opr;
    InitStack(opr);
    while(exp[i] != '\0')
    {
        GetTop(opr,e);
        switch(exp[i])
        {
            case '+':
            case '-':
                if(IsStackEmpty(opr)||e =='(')
                    PushStack(opr,exp[i]);
                else
                {
                    PopStack(opr,e);
                    postexp[j++] = e;
                    PushStack(opr,exp[i]);
                }
                i++;
                break;
            case '*':
            case '/':
                if(IsStackEmpty(opr)||e =='('||e == '+'||e == '-')
                    PushStack(opr,exp[i]);
                else
                {
                    PopStack(opr,e);
                    postexp[j++] = e;
                    PushStack(opr,exp[i]);
                }
                i++;
                break;
            case '(':
                PushStack(opr,exp[i]);
                i++;
                break;
            case ')':
                while (GetTop(opr, e) && e != '(') 
                { 
                    PopStack(opr, e);
                    postexp[j++] = e;
                }
                PopStack(opr, e);
                i++;
                break;
            default:
                while(exp[i]>='0'&&exp[i]<='9')
                    postexp[j++] = exp[i++];
                postexp[j++] = '#';
                break;
        }
    }
    while(!IsStackEmpty(opr))
    {
        PopStack(opr,e);
        postexp[j++] = e;
    }
    postexp[j] = '\0';
    DestroyStack(opr);
}

double calculate(char *postexp)
{
    double a,b,c,d,e; 
    SqStack_double *s;
    InitStack(s);
    while(*postexp != '\0')
    {
        switch(*postexp)
        {
            case '+':
                PopStack(s,a);
                PopStack(s,b);
                c = b+a;
                PushStack(s,c);
                break;
            case '-':
                PopStack(s,a);
                PopStack(s,b);
                c = b-a;
                PushStack(s,c);
                break;
            case '*':
                PopStack(s,a);
                PopStack(s,b);
                c = b*a;
                PushStack(s,c);
                break;
            case '/':
                PopStack(s,a);
                PopStack(s,b);
                if(a==0)
                {
                    cout<<"wrong!"<<endl;
                    exit(0);
                }
                else
                {
                    c = b/a;
                    PushStack(s,c);
                    break;
                }
            default:
                d = 0;
                while(*postexp>='0'&&*postexp<='9')
                {
                    d = 10*d + *postexp - '0';
                    postexp++;
                }
                PushStack(s,d);
                break;
            }
            postexp++;
        }
        GetTop(s,e);
        DestroyStack(s);
        return e;
    }

int main()
{
    char postexp[MAX];
    char exp[MAX];
    cin>>exp;
    trans(postexp,exp);
    cout<<exp<<endl;
    cout<<postexp<<endl;
    cout<<calculate(postexp)<<endl;
    return 0;
}