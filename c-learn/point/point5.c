#include <stdio.h>
void Fun(int par){
    printf("par=%d\n",par);
    par=2;
}
int main(void){
    int arg=1;
    printf("before change,arg is %d\n",arg);
    Fun(arg);
    printf("after change,arg is %d\n",arg);
    return 0;
}
/*输出结果：
before change,arg is 1
par=1
after change,arg is 1
从输出结果可以看出，函数Fun中的参数par在函数调用时接收了实参arg的值，但对par的修改并没有影响到arg的值。
这是因为C语言中的函数参数传递是通过值传递的方式进行的，即将实参的值复制一份传递给形参。因此，在函数内部对形参par的修改不会影响到实参arg的值。
需要注意的是，如果希望在函数内部修改实参的值，可以通过传递指针来实现，即传递实参的地址，这样函数内部就可以通过指针间接地修改实参的值。
总结：通过打印函数参数的值，可以观察到函数参数传递的方式及其对实参的影响，但具体的传递方式需要根据函数定义和调用方式进行分析。本例仅供参考。
指针传递见point6.c
*/