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
void ReadfromFile(Student stu[],int *n, int *m);
void Printscore (Student stu[],int n, int m);

int main()
{
    Student stu[N];
    int n,m=4;
    ReadfromFile(stu,&n,&m);
    Printscore(stu,n,m);
    system("PAUSE");
    return 0;
}

void Printscore(Student stu[],int n,int m){
    for(int i=0;i<n;i++){
        printf("%10ld%8s%3c%6d/%02d/%02d",stu[i].studentID,stu[i].studentName,stu[i].studentsex,stu[i].birthday.year,stu[i].birthday.month,stu[i].birthday.day);
        for(int j=0;j<m;j++){
            printf("%4d",stu[i].socre[j]);
        }
        printf("%6.1f\n",stu[i].aver);
    }
}

void ReadfromFile(Student stu[],int *n, int *m){
    FILE*fp;
    if((fp=fopen("score.txt","r"))==NULL){
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp, "%d\t%d\n",n,m);
    for(int i=0; i<*n; i++){
        fscanf(fp,"%10ld",&stu[i].studentID);
        fscanf(fp,"%8s",stu[i].studentName);
        fscanf(fp," %c",&stu[i].studentsex);
        fscanf(fp,"%6d/%2d/%2d",&stu[i].birthday.year,&stu[i].birthday.month,&stu[i].birthday.day);
        for(int j=0;j<*m;j++){
            fscanf(fp,"%4d",&stu[i].socre[j]);
        }
        fscanf(fp,"%f",&stu[i].aver);
    }
    fclose(fp);
}