#include <stdio.h>
int judgeLegal(int year,int month,int day,int Day[2][12]);
int main(void)
{
    int year=1990,month=01,day=01;
    scanf("%4d-%2d-%2d",&year,&month,&day);
    int i=0,j=0,k=0;
    int deltadays=0;
    int Day[2][12]= {{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
    if(judgeLegal(year,month,day,Day)){
        int isLeapYear=0;
        if (year%4==0&&year%100!=0){
            isLeapYear=1;
        }
        for(i=1990; i<year; i++)
        {
            int isLeapYear=0;
            if (i%4==0&&i%100!=0)
            {
                deltadays+=366;
                isLeapYear=1;
            }
            else {
                deltadays+=365;
            }
            
        }
        for (j=01; j<month; j++){
            deltadays+=Day[isLeapYear][j-1];
        }

        deltadays+=day;
        switch(deltadays%5)
        {
        case 1:
        case 2:
        case 3:
            printf("working\n");
            break;
        case 4:
        case 0:
            printf("rest\n");

        }
    }else{
        printf("Invalid input\n");
    }

    return 0;
}
int judgeLegal(int year,int month,int day,int Day[2][12])
{
    int isLeapYear=0;
    int legal=1;
    if (year%4==0&&year%100!=0)
    {
        isLeapYear=1;
    }
    if(year<1990||month<01||month>12||day<01||day>Day[isLeapYear][month-1]){
        legal=0;
    }
    return legal;
}