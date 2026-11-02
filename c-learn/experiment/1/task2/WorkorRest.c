#include <stdio.h>
int isLeapYear(int year);
int main(void){
    int year,month,day,originYear,originMonth,originDay;
    int deltaDays=0;
    printf("渔夫是什么时候开始打渔的，请输入年月日，用-隔开：\n");
    scanf("%d-%d-%d",&originYear,&originMonth,&originDay);
    printf("请输入你想查询的日期年月日，用-隔开：\n");
    scanf("%d-%d-%d",&year,&month,&day);

    int monthDays[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},
                        {31,29,31,30,31,30,31,31,30,31,30,31}};
    //处理不合法数据
    if(year<originYear||(year==originYear&&month<originMonth)||(year==originYear&&month==originMonth&&day<originDay||month<1||month>12||day<1||day>monthDays[isLeapYear(year)][month-1])){
        printf("Invalid input\n");
        return 0;
    }
    //计算时间差
    int i,j,k;

    //计算年份差距并转化为天数
    for(i=originYear;i<year;i++){
        if(isLeapYear(i)){
            deltaDays+=366;
        }
        else{
            deltaDays+=365;
        }
    }

    //计算月份差距并转化为天数
    if(originMonth<=month){
        for(j=originMonth;j<month;j++){
        deltaDays+=monthDays[isLeapYear(year)][j-1];
    }
    }
    else {
        for(j=originMonth;j>month;j--){
            deltaDays-=monthDays[isLeapYear(year)][j-2];
        }
    }
    //处理好月份有负数的情况

    //计算天数差距
    if(originDay<=day){
        deltaDays+=day-originDay;
    }
    else {
        deltaDays-=originDay-day;
    }

    //利用deltaDays计算是否打渔
    switch (deltaDays%5){
        case 0:
        case 1:
        case 2:
            printf("working\n");
            break;
        case 3:
        case 4:
            printf("rest\n");
            break;
    }
    return 0;
}
int isLeapYear(int year){
    int isLeapYear=0;
    if(year%4==0&&year%100!=0||year%400==0){
        isLeapYear=1;
    }
    return isLeapYear;
}