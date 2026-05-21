#include<stdio.h>
#include<stdlib.h>
#define N 30
typedef struct DATE{
    int year;
    int month;
    int day;
}date;
typedef struct student{
    long studentID;
    char studentname[10];
    char studentsex;
    date birthday;
    int score[4];
    float aver;
}Student;
void Searchinfile(char filename[],long k);
int main()
{
    long k;
    printf("Input the searching record number:");
    scanf("%ld",&k);
    Searchinfile("student.txt",k);
    system("PAUSE");
    return 0;
}
void Searchinfile(char filename[],long k){
    FILE*fp;
    int j;
    Student stu;
    if((fp=fopen(filename,"r"))==NULL){
        printf("Failure to open %s\n ",filename);
        exit(0);
    }
    fseek(fp,(k-1)*sizeof(Student),0);
    fread(&stu,sizeof(Student),1,fp);
    printf("%10ld%8s%3c%6d/%02d/%02d",stu.studentID,stu.studentname,stu.studentsex,stu.birthday.year,stu.birthday.month,stu.birthday.day);
    for(j=0;j<4;j++){
        printf("%4d",stu.score[j]);
    }
    printf("%6.1f\n",stu.aver);
    fclose(fp);
}