#include <stdio.h>
#define N 20
int main(void){
    char name[N];
    printf("请输入你的名字：\n");
    fgets(name,sizeof(name),stdin);
    printf("你好,");
    puts(name);
    return 0;
}