#include <stdio.h>
# define MONTHS 12
int main(){
    int days[MONTHS]={31,28,31,30,31,30,31,31,30,31,30,31};
    int month=0;
    do{
        printf("请输入您想要查询的月份：\n");
        scanf("%d",&month);
    }while(month<1||month>12);
    printf("%d月份的天数为%d天",month,days[month-1]);
    return 0;
    }
