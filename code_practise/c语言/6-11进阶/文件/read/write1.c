#include<stdio.h>
#include<stdlib.h>
#define N 30
typedef struct date
{
    int year;
    int month;
    int day;
}Date;
typedef struct student
{
    long studentID;
    char studentName[10];
    char studentsex;
    Date birthday;
    int socre[4];
    float aver;
}Student;
void Inputscore(Student stu[],int n, int m);
void Averscore (Student stu[],int n, int m);
void Write_to_file(Student stu[],int n, int m);
int main()
{
    Student stu[N];
    int n;
    printf("How many student?\n");
    scanf("%d", &n);
    Inputscore(stu,n,4);
    Averscore(stu,n,4);
    Write_to_file(stu,n,4);
    system("PAUSE");
    return 0;
}

void Inputscore(Student stu[],int n, int m){
    for(int i=0;i<n;i++){
        printf("Input record %d:\n",i+1);
        scanf("%ld",&stu[i].studentID);
        scanf("%s",&stu[i].studentName);
        scanf(" %c",&stu[i].studentsex);
        scanf("%d",&stu[i].birthday.year);
        scanf("%d",&stu[i].birthday.month);
        scanf("%d",&stu[i].birthday.day);
        for(int j=0;j<m;j++){
            scanf("%d",&stu[i].socre[j]);
        }
    }
}

void Averscore (Student stu[],int n, int m){
    int sum;
    for(int i=0; i<n; i++){
        sum = 0;
        for(int j=0;j<m;j++){
            sum+=stu[i].socre[j];
        }
        stu[i].aver=(float)sum/m;
    }
}

void Write_to_file(Student stu[],int n, int m){
    FILE*fp;
    if((fp=fopen("score.txt","w"))==NULL){
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fprintf(fp, "%d\t%d\n",n,m);
    for(int i=0; i<n; i++){
        fprintf(fp,"%10ld%8s%3c%6d/%02d/%02d",stu[i].studentID,stu[i].studentName,stu[i].studentsex,stu[i].birthday.year,stu[i].birthday.month,stu[i].birthday.day);
        for(int j=0; j<m; j++){
            fprintf(fp,"%4d",stu[i].socre[j]);
        }
        fprintf(fp,"%6.1f\n", stu[i].aver);
    }
    fclose(fp);
}