#include <stdio.h>
#define N 20
int main(void){
    char name[N];
    char *ptr="\"Hello\",I said to";
    printf("请输入你的名字：\n");
    fgets(name,sizeof(name),stdin);
    printf("%s %s.\n",ptr,name);
    return 0;
}
//"看不懂字符数组和字符指针在使用上的不同之..."点击查看元宝的回答
//https://yb.tencent.com/s/IrJ6aTRf0cCS