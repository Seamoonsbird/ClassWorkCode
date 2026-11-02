//采用穷举法，用函数编程实现计算两个正整数的最小公倍数的函数，在主程序中调用该函数计算并输出从键盘任意输入的两正整数的最小公倍数。
#include <stdio.h>
int lcm(int a,int b);
int main(void){
    int a=0,b=0;
    printf("请输入两个正整数：例如2 5\n");
    scanf("%d %d",&a,&b);
    printf("最小公倍数为：%d\n",lcm(a,b));
    return 0;
}
int lcm(int a,int b){
    int lcm=a>b?a:b;
    while(lcm%a!=0||lcm%b!=0){
        lcm++;
    }
    return lcm;
}