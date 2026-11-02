/*
题目描述
“冰雹猜想”（又称角谷猜想）：一个正整数n，若为偶数则除以2，若为奇数则乘以3再加1。循环执行此操作，最终都能回到1。
核心要求
编写C语言递归函数countSteps，接收正整数n作为参数，计算该数字按规则变换到1所需的总步数。
递归规则
1.	终止条件：n=1时返回0。
2.	偶数n：下一步为n/2，步数+1后递归。
3.	奇数n：下一步为3n+1，步数+1后递归。
*/
#include <stdio.h>
int countSteps(int n);
int main(void){
    int n=0;
    printf("请输入你要求的数字：");
    scanf("%d",&n);
    printf("所需要的次数为：%d\n",countSteps(n));
    return 0;
}
int countSteps(int n){
    if (n%2==0&&n!=1){
        return 1+countSteps(n/2);
    }
    else if(n%2==1&&n!=1){
        return 1+countSteps(n*3+1);
    }
    else {
        return 0;
    }
}