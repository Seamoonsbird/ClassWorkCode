#include <stdio.h>
int main(void){
    int a=0,b=1;
    char c='a';
    int *pa,*pb;
    char *pc;
    pa=&a;
    pb=&b;
    pc=&c;
    printf("a is %d,&a is %p,pa is %p,&pa is %p\n",a,&a,pa,&pa);
    printf("b is %d,&b is %p,pa is %p,&pa is %p\n",b,&b,pb,&pb);
    printf("c is %c,&c is %p,pa is %p,&pc is %p\n",c,&c,pc,&pc);
    return 0;
}
/*输出结果：
a is 0,&a is 00000000005FFE6C,pa is 00000000005FFE6C,&pa is 00000000005FFE58
b is 1,&b is 00000000005FFE68,pa is 00000000005FFE68,&pa is 00000000005FFE50
c is a,&c is 00000000005FFE67,pa is 00000000005FFE67,&pc is 00000000005FFE48
从输出结果可以看出，指针变量pa、pb、pc存储了变量a、b、c的地址，并且指针变量本身也有自己的地址。
这是因为指针变量用于存储另一个变量的地址，因此它们的值（即指向的地址）与它们自身的地址是不同的。
需要注意的是，指针变量的地址分配方式与普通变量类似，可能会受到编译器的对齐处理影响，因此在某些情况下，指针变量的地址可能不是完全连续的。
总结：通过打印指针变量及其指向变量的地址，可以观察到指针变量在内存中的分配情况，但具体的地址分配方式可能因编译器和操作系统而异，需要根据具体情况进行分析。本例仅供参考。
*/