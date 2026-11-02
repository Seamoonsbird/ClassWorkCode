#include <stdio.h>
int main (){
    int a,b;
    printf("请输入两个正整数\n");
    scanf("%d %d",&a,&b);
    int t=0;
    while(b!=0){
        t=a%b;
        a=b;
        b=t;
    }
    printf("最大公约数为%d\n",a);
    return 0;

}
