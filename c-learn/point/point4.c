#include <stdio.h>
int main(void){
    int a=0,b=1;
    char c='a';
    int *pa,*pb;
    char *pc;
    pa=&a;
    pb=&b;
    pc=&c;
    printf("a is %d,&a is %p,pa is %p,&pa is %d\n",a,&a,pa,*pa);
    printf("b is %d,&b is %p,pa is %p,&pa is %d\n",b,&b,pb,*pb);
    printf("c is %c,&c is %p,pa is %p,&pc is %c\n",c,&c,pc,*pc);
    printf("--------after change--------\n");
    *pa=9;
    printf("a is %d,&a is %p,pa is %p,&pa is %d\n",a,&a,pa,*pa);
    printf("b is %d,&b is %p,pa is %p,&pa is %d\n",b,&b,pb,*pb);
    printf("c is %c,&c is %p,pa is %p,&pc is %c\n",c,&c,pc,*pc);
    return 0;
}