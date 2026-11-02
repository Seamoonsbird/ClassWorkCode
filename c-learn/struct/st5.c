#include <stdio.h>
struct date{
    int year;
    int month;
    int day;
};
struct date Func(struct date p){
    p.year=2024;
    p.month=6;
    p.day=30;
    return p;
}
int main(void){
    struct date d;
    d.year=2000;
    d.month=1;
    d.day=1;
    printf("before Func:d=%d/%02d/%02d\n",d.year,d.month,d.day);
    d=Func(d);
    printf("after  Func:d=%d/%02d/%02d\n",d.year,d.month,d.day);
    return 0;
}