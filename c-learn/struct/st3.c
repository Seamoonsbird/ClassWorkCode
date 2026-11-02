#include <stdio.h>
typedef struct date{
    int year;
    int month;
    int day;
}DATE;
typedef struct student{
    long studentID;
    char studentName[20];
    char studentSex;
    DATE birthday;
    int score[4];
}STUDENT;
int main(void){
    int i,j,sum[30];
    STUDENT stu[30]={{1,"john",'M',{2000,1,1},{90,91,92,93}},
                     {2,"mary",'F',{2001,2,2},{85,86,87,88}},
                     {3,"tom",'M',{2002,3,3},{80,81,82,83}},
                     {4,"lily",'F',{2003,4,4},{75,76,77,78}}};
    for (i=0;i<4;i++){
        sum[i]=0;
        for (j=0;j<4;j++){
            sum[i]+=stu[i].score[j];
        }
        printf("%10ld %8s %3c %6d/%02d/%02d %4d %4d %4d %4d%6.1f\n",
                stu[i].studentID,
                stu[i].studentName,
                stu[i].studentSex,
                stu[i].birthday.year,
                stu[i].birthday.month,
                stu[i].birthday.day,
                stu[i].score[0],
                stu[i].score[1],
                stu[i].score[2],
                stu[i].score[3],
               (double)sum[i]/4);
    }
    return 0;
}