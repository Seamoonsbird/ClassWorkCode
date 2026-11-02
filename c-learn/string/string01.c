#include <stdio.h>
#define N 20
int main(void){
    char name[N];
    printf("请输入你的名字：\n");
    scanf("%s",name);
    printf("你好，%s!\n",name);
    return 0;
}