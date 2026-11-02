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
    DATE birthday;//结构体嵌套
    int score[4];
}STUDENT;
int main(void){
    STUDENT stu1={2025310410,"haha",'M',{1990,1,1},{72,83,90,82}};
    STUDENT stu2;
    stu2=stu1;//结构体变量之间可以直接赋值
    printf("stu2:%10ld %8s %3c %6d/%02d/%02d %4d %4d %4d %4d\n",
           stu2.studentID,stu2.studentName,stu2.studentSex,
           stu2.birthday.year,stu2.birthday.month,stu2.birthday.day,
           stu2.score[0],stu2.score[1],stu2.score[2],stu2.score[3]);
    return 0;
}