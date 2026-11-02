#include <stdio.h>
struct date{
    int year;
    int month;
    int day;
};
void Func(struct date *pt){
    pt->year=2024;
    pt->month=6;
    pt->day=30;
}
int main(void){
    struct date d;
    d.year=2000;
    d.month=1;
    d.day=1;
    printf("before Func:d=%d/%02d/%02d\n",d.year,d.month,d.day);
    Func(&d);
    printf("after  Func:d=%d/%02d/%02d\n",d.year,d.month,d.day);
    return 0;
}