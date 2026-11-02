//使用递归函数实现计算n的k次方，其中n与k均为正整数。
#include <stdio.h>
int power(int n,int k);
int main(void){
    int n,k;
    printf("请输入两个正整数n和k，用来计算n的k次方的值：\n");
    scanf("%d %d",&n,&k);
    if(power(n,k)==-1){
        printf("我还不会算负数次方，放过我吧！\n");
        return 0;
    }
    if(power(n,k)>0){
    printf("%d的%d次方是：%d\n",n,k,power(n,k));
    return 0;
    }
}
int power(int n,int k){
    if (k<0){
        return -1;
    }
    else if (k==0){
        return 1;
    }
    else{
        return n*power(n,k-1);
    }
}