#include<stdio.h>
int main()
{
    char c = -1;
    int i = -1;
    printf("c=%u,i=%u\n", c,i);//%u以unsigned且char转为高字节int
    char a=012;
    int b=0x12;
    printf("a=%d,b=%d\n",a,b);//%d为十进制；0%o为八进制；0x%x为十六进制 小写对应小写（输出
    return 0;
}