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
void inputscore(Student stu[],int n, int m);
void averscore(Student stu[],int n, int m);
void writetofile(Student stu[], int n);
int readfromfole(Student stu[]);
void Printscore(Student stu[], int n,int m);
int main()
{
    Student stu[N];
    int n,m=4;
    printf("How many students?\n");
    scanf("%d",&n);
    inputscore(stu,n,m);
    averscore(stu,n,m);
    writetofile(stu,n);
    n=readfromfole(stu);
    Printscore(stu,n,m);
    system("PAUSE");
    return 0;
}

void inputscore(Student stu[],int n, int m)
{
    for(int i=0;i<n;i++){
        printf("Record %d\n",i+1);
        scanf("%ld",&stu[i].studentID);
        scanf("%s",stu[i].studentname);
        scanf(" %c",&stu[i].studentsex);
        scanf("%d",&stu[i].birthday.year);
        scanf("%d",&stu[i].birthday.month);
        scanf("%d",&stu[i].birthday.day);
        for(int j=0;j<m;j++){
            scanf("%d",&stu[i].score[j]);
        }
    }
}

void averscore(Student stu[],int n, int m)
{
    int sum=0;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=0;j<m;j++){
            sum+=stu[i].score[j];
        }
        stu[i].aver=(float)sum/m;
    }
}

void writetofile(Student stu[], int n)
{ 
    FILE*fp;
    if((fp=fopen("student.txt","wb"))==NULL){
        printf("Failure to open student.txt\n");
        exit(0);
    }
    fwrite(&n, sizeof(int), 1, fp); 
    fwrite(stu,sizeof(Student),n,fp);
    fclose (fp);
}

int readfromfole(Student stu[])
{
    FILE *fp;
    int i,n;
    if((fp=fopen("student.txt","rb"))==NULL){
        printf("Failure to open student.txt\n");
        exit(0);
    }
    fread(&n,sizeof(int),1,fp);
    for(i=0;!feof(fp);i++){
        fread(&stu[i],sizeof(Student),1,fp);
    }
    fclose(fp);
    printf("Total students is %d.\n",i-1);
    return i-1;
}

void Printscore(Student stu[], int n,int m)
{
    for(int i=0;i<n;i++){
        printf("%10ld%8s%3c%6d/%02d/%02d",stu[i].studentID,stu[i].studentname,stu[i].studentsex,stu[i].birthday.year,stu[i].birthday.month,stu[i].birthday.day);
        for(int j=0;j<m;j++){
            printf("%4d",stu[i].score[j]);
        }
        printf("%6.1f\n",stu[i].aver);
    }
}