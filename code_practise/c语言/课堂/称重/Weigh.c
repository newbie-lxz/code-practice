#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int FLAG=0,sum1=0,sum2=0;
void Weigh(int N,int n,int *p1,int *p,int *d);
int Determine(int sum1,int sum2);
void result(int *deter,int *p1,int N,int n);
int flag(int *deter,int *p1,int *rev,int i,int N);
int main()
{
    int n,N,faulty,weight,*num,*norm,*rev,*deter;
    printf ("please input the number of balls ");
    scanf("%d",&n);
    if(n<=2)  //如果球个数少于三个那称多少次也是称不出来滴
    {
        printf("God Bless You");
        exit(0);
    }
    N=(int)ceil(log10((double)(2*n+3))/(double)log10(3)); //在要求知道结束时问题球偏轻还是偏重时最少次数N=log3（2n+3）向上取整次
    FLAG=n%3;  //如果不是三的倍数需要在后续编号时把第n号空出，使用n+1行，以保证第一次称球两边球数量相等，后续哪边缺就加正常质量的球就行
    if(FLAG==1&&n!=13)
    {
        n++;
    }
    if(n==13)
    {
        N=3;
    }  
    num=(int*)calloc(n*2,sizeof(int));
    deter=(int*)calloc(N,sizeof(int));
    for(int i=0;i<n;i++)
    {
        num[i*2]=i; //第一列代表编号
        num[i*2+1]=1; //第二列代表质量，初始化为1
    }
    printf("Which ball would be faulty? ");
    scanf("%d",&faulty);
    printf("Would it be lighter(0) or heavier(2)? ");
    scanf("%d",&weight);
    if(weight==0||weight==2)
        num[(faulty-1)*2+1]=weight;
    else 
    {
        printf("input error\n");
        exit(1);
    }
    norm=(int*)calloc(n*N,sizeof(int));
    rev=(int*)calloc(n*N,sizeof(int));
    Weigh(N,n,norm,num,deter);
    free(num);
    free(norm);
    free(rev);
    free(deter);  
    return 0;
}
void Weigh(int N,int n, int *p1,int *p,int *deter)
{
    p1[N-1]=1;
    for(int i=0;i<N-1;i++)
    {
        p1[i]=0;
    }
    for(int i=1;i<n;i++)   //根据小球个数进行三进制编码（直到第130行代码）
    {
        if(i%3==0)        //每三行一组，每组第一行是上一组第一行三进制加一直到第一个非零位是1
        {
            for(int k=i*N;k<(i+1)*N;k++)    //先将本组第一行复制上一组第一行
            {
                p1[k]=p1[k-3*N];
            }
            p1[(i+1)*N-1]=p1[(i-2)*N-1]+1;  //先尝试在个位加一
            for(int a=0;a<N;a++)
                {
                    if(p1[(i+1)*N-a-1]==3)   //三进制逢三进一捏
                    {
                        p1[(i+1)*N-a-2]++;
                        p1[(i+1)*N-a-1]=0;
                    }
                }
            while(1)
            {
                int k=0;
                while(p1[i*N+k]==0)   //通过k让指针对准这一行第一个不是0的数
                {
                    k++;
                }
                if(p1[i*N+k]==1)     //检验是否是1，如果是的就可以结束啦
                {
                    break;
                }
                else                //如果不是就得继续个位加一
                {
                    p1[(i+1)*N-1]++;
                }
                for(int a=0;a<N;a++)  //继续检查逢三进一
                {
                    if(p1[(i+1)*N-a-1]==3)
                    {
                        p1[(i+1)*N-a-2]++;
                        p1[(i+1)*N-a-1]=0;
                    }
                }
            }
        continue; //这一行编辑就结束了，不用进入106-115行内容了
        }
        for(int j=0;j<N;j++)  //如果是每组的第二、三行就可以直接在上一行的基础上每位加一即可
        {
            
            p1[i*N+j]=p1[(i-1)*N+j]+1;
            if(p1[i*N+j]==3)   //如果加到3了变0即可
            {
                p1[i*N+j]=0;
            }
        }
    }
    if(n==13)
    {
        for(int j=0;j<3;j++)
        {
            p1[12*3+j]=1;
        }
    }
    if(FLAG==1&&n!=13)    //如果除3余1上面多加一行是为了在第一次称量时把原来最后一行第一位是0的给扔了，保证第一次称量时天平两端球数相等
    {
        for(int j=0;j<N;j++)  
        {
            p1[(n-2)*N+j]=p1[(n-1)*N+j];  //把多加的一行的三进制编码赋给原来的最后一行就可以把多加的一行扔了
        }
        n-=1;
    }
    for(int i=0;i<N;i++)   //开始放置天平，一共N次
    {
        int counter1=0,counter2=0;
        sum1=0;
        sum2=0;
        printf("第%d次",i+1);
        for(int j=0;j<n;j++)
        {
            if(p1[j*N+i]==0)  //第i位为0的第i次称量时放在天平左边
            {
                printf("%d号小球,",j+1);
                counter1++;
                sum1+=p[j*2+1];    //把num数组第二列代表质量的全部加起来，131行同理
            }
        }
        if((FLAG==1&&counter1<(n-1)/3+1&&n!=13)||(FLAG==2&&counter1<(n+1)/3))//不是3倍数的情况会出现一边少球，要补上
        {
            for(int k=0;k<N;k++)
            {
                if(p[k*2+1]==1&&p1[k*N+i]==1)//找一个没上场的正常球，赶紧补上（
                {
                    sum1++;
                    printf("%d号小球,",k+1);
                    break;
                }
            }
        }
        printf("在天平左边,");
        for(int j=0;j<n;j++)  //第i位为2的第i次称量时放在天平右边
        {
            if(p1[j*N+i]==2)
            {
                counter2++;
                printf("%d号小球,",j+1);
                sum2+=p[j*2+1];
            }
            
        }
        if((FLAG==1&&counter2<(n-1)/3+1&&n!=13)||(FLAG==2&&counter2<(n+1)/3))
        {
            for(int k=0;k<N;k++)
            {
                if(p[k*2+1]==1&&p1[k*N+i]==1)
                {
                    sum2++;
                    printf("%d号小球,",k+1);
                    break;
                }
            }
        }
        printf("在天平右边\t"); //后续如果n不是3的倍数会出现两边球数量不相等的情况，需要补上正常质量小球。第一次称完肯定能发现正常小球的，因为如果天平倾斜就是没上秤的正常，平衡就是上秤的正常
        deter[i]=Determine(sum1,sum2); //将Determine得到的N个值输入deter数组中
    }
    printf("\n");
    result(deter,p1,N,n);
}
int Determine(int sum1,int sum2) //判断天平向哪倾斜，如果左边重返回2，如果一样重返回1，如果右边重返回0
{
    int det;
    if(sum1<sum2)
    {
        det=2;
        printf("天平向右边倾斜\n");
    }
    else if(sum1==sum2)
    {
        det=1;
        printf("天平平衡\n");
    }
    else if(sum1>sum2)
    {
        det=0;
        printf("天平向左边倾斜\n");
    }
    return det;
}
void result(int *deter,int *p1,int N,int n) //根据deter数组中的数得出是哪个球有问题，如果和原三进制编号的p1数组中第n行相同，
{                                           //说明第n个球偏重，如果和p1的逆序（见下文解释)第n行相同，说明第n个球偏轻
    int rev[n][N];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<N;j++) //p1的逆序即将p1中全部2变成0，0变成2，1不变
        {
            if(p1[i*N+j]==2)
            {
                rev[i][j]=0;
            }
            else if(p1[i*N+j]==0)
            {
                rev[i][j]=2;
            }
            else if(p1[i*N+j]==1)
            {
                rev[i][j]=1;
            }
        }
    }
        for(int i=0;i<n;i++)
        {
            if(flag(deter,p1,*rev,i,N)==1)  //第一想法是在if里套个for循环，因为要检测每一位
            {                               //不过好像不行，那就让函数返回吧
                printf("%d号球偏重!",i+1);
            }
            if(!flag(deter,p1,*rev,i,N))
            {
                printf("%d号球偏轻!",i+1);
            }
        }
}
int flag(int *deter,int *p1,int *rev,int i,int N)  
{                                                  
    int count1=0,count2=0;
    for(int j=0;j<N;j++)
    {
        if(deter[j]==p1[i*N+j])
        {
            count1++;
        }
        else
        {
            break;
        }
    }
    for(int j=0;j<N;j++)
    {
        if(deter[j]==rev[i*N+j])
        {
            count2++;
        }
        else
        {
            break;
        }
    }
    if(count1==N) //必须N位全部相同
    {
        return 1;
    }
    else if(count2==N)
    {
        return 0;
    }
    else
    {
        return 114514; //肯定两个数组里有一个是可以的，没有的话说明程序出大问题了
    }
}