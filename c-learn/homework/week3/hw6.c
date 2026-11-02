//设某大学有下列登记表，采用最佳方式对它进行类型定义。
//根据上题中的结构体类型，定义一个大小为5的结构体数组，输入5名人员的信息，并输出年龄最大的人员姓名。
#include <stdio.h>
typedef struct DATE
{
    int year;
    int month;
    int day;
}DATE;
typedef struct status
{
    char school[50];
    char jobtitle[50];
    char position[50];
}STATUS;
typedef struct person
{
    char name[20];
    char sex;
    DATE birthday;
    STATUS jobstatus;
}PERSON;
DATE findmax(PERSON per[],int n);
int jungledate(DATE d1,DATE d2);
int main(void){
    PERSON per[5];
    int i=0;
    printf("请输入5名成员的信息：\n");
    for (i=0;i<5;i++){
        scanf("%s",per[i].name);
        scanf(" %c",&per[i].sex);
        scanf("%4d",&per[i].birthday.year);
        scanf("%2d",&per[i].birthday.month);
        scanf("%2d",&per[i].birthday.day);
        scanf("%s",per[i].jobstatus.school);
        scanf("%s",per[i].jobstatus.jobtitle);
        scanf("%s",per[i].jobstatus.position);
    }
    DATE max=findmax(per,5);
    int counts=0;
    for (i=0;i<5;i++){
        if (jungledate(per[i].birthday,max)==-1){
            printf("年龄最大的人员姓名为：%s\n",per[i].name);
            counts++;
        }
    }
    if (counts>1){
        printf("共有%d名年龄最大的人员。\n",counts);
    }
    return 0;
}

DATE findmax(PERSON per[],int n){
    int i=1;
    DATE k=per[0].birthday;
    for (i=1;i<5;i++){
        if (jungledate(per[i].birthday,k)==1){
            k=per[i].birthday;
        }
    }
    return k;
}

int jungledate(DATE d1,DATE d2){
    if (d1.year<d2.year){
        return 1;
    }
    else if (d1.year>d2.year){
        return 0;
    }
    else{
        if (d1.month<d2.month){
        return 1;
    }
    else if (d1.month>d2.month){
        return 0;
    }
    else{
        if (d1.day<d2.day){
            return 1;
        }
    else if (d1.day>d2.day){
        return 0;
    }
    else{
        return -1;
    }
    }
    }
}

