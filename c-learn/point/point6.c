#include <stdio.h>
void Fun(int *par){
    printf("par=%d\n",*par);
    *par=2;
}
int main(void){
    int arg=1;
    printf("before change,arg is %d\n",arg);
    Fun(&arg);
    printf("after change,arg is %d\n",arg);
    return 0;
}
/*输出结果：
before change,arg is 1
par=1
after change,arg is 2
从输出结果可以看出，函数Fun中的参数par在函数调用时接收了实参arg的地址，通过指针间接修改了arg的值。
这是因为C语言中的函数参数传递是通过值传递的方式进行的，即将实参的值复制一份传递给形参。但是当传递的是指针时，传递的是地址的值，因此函数内部可以通过指针间接地修改实参的值。
需要注意的是，使用指针传递参数时，必须确保传递的地址是有效的，否则可能会导致未定义行为。
总结：通过打印函数参数的值，可以观察到指针传递参数的方式及其对实参的影响，但具体的传递方式需要根据函数定义和调用方式进行分析。本例仅供参考。
*/