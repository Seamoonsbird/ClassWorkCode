#include<stdio.h>
#define MONTHS 12
int main(){
    int month=0;
    int year=2025;
    int YEAR=0;
    int days[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
    do{printf("请输入想要查询的年份与月份:\n");
    scanf("%d %d",&year,&month);
    }while(month<1||month>12);
    if ((year%4==0)&&(year%100!=0)||(year%400==0)){
        ++YEAR;
    }
    printf("该月份的天数为：%d\n",days[YEAR][month-1]);//一定要记得month-1 
    return 0;
    }
