#include<stdio.h>
#include<stdlib.h>
#define N 30
typedef struct date{
    int year;
    int month;
    int day;
}DATE;

typedef struct information{
    long id;
    char name[100];
    char gender;
    DATE birthday;
    float score[4];
}INFORMATION;

void inputinformation(INFORMATION stu[], int n);
void calculateaverage(INFORMATION stu[], int n, float aver[]);
void output(INFORMATION stu[], int n, float aver[]);

int main()
{
    int n;
    float aver[N];
    INFORMATION stu[N];
    printf("The number of student is :");
    scanf("%d",&n);
    
    inputinformation(stu, n);
    calculateaverage(stu, n, aver);
    output(stu, n, aver);

    return 0;
}

void inputinformation(INFORMATION stu[], int n)
{
    for(int i=0; i<n; i++){
        printf("Input record %d:\n",i+1);
        scanf("%ld",&stu[i].id);
        scanf(" %s",stu[i].name);
        scanf(" %c",&stu[i].gender);
        scanf("%d",&stu[i].birthday.year);
        scanf("%d",&stu[i].birthday.month);
        scanf("%d",&stu[i].birthday.day);
        for(int j=0; j<4; j++){
            scanf("%f",&stu[i].score[j]);
        }
    }
}

void calculateaverage(INFORMATION stu[], int n, float aver[])
{
    for(int i=0; i<n; i++){
        float sum=0;
        for(int j=0; j<4; j++){
            sum+= stu[i].score[j];
        }
        aver[i]=sum/4;
    }
}

void output(INFORMATION stu[], int n, float aver[])
{
    int i,j;
    printf("Results:\n");
    for(i=0; i<n; i++){
        printf("%-8ld%-5s%-3c%2d/%2d/%2d",stu[i].id,stu[i].name,stu[i].gender,stu[i].birthday.year,stu[i].birthday.month,stu[i].birthday.day);
        for(j=0; j<4; j++){
            printf("%6.2f",stu[i].score[j]);
        }
        printf("%6.2f",aver[i]);
    }
}