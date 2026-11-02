#include <stdio.h>
#define N 20
int main(void){
    char name[N];
    char *ptrname=name;
    printf("请输入你的名字：\n");
    gets(ptrname);
    printf("你好,");
    puts(ptrname);
    return 0;
}
//使用字符指针