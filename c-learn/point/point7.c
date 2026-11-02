#include <stdio.h>
void swap(int *a,int *b){
    int t;
    t=*a;
    *a=*b;
    *b=t;
}
int main(void){
    int a,b;
    printf("please input a&b:\n");
    scanf("%d %d",&a,&b);
    printf("before change,a is %d,b is %d\n",a,b);
    swap(&a,&b);
    printf(" after change,a is %d,b is %d\n",a,b);
    return 0;
}