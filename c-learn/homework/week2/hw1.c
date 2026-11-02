//用函数编程计算两整数的最大值，在主函数中调用该函数计算并输出从键盘任意输入的两整数的最大值。
#include <stdio.h>
int max(int a,int b);
int main(void){
    int a,b;
    printf("请输入两个整数：例如2 5\n");
    scanf("%d %d",&a,&b);
    printf("最大值是：%d\n",max(a,b));
    return 0;
}
int max(int a,int b){
    return a>b?a:b;
}