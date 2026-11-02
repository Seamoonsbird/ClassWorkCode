#include <stdio.h>
unsigned long mystrlen(const char str[]);
int main(void){
    int i;
    char string[80];
    printf("请输入一个字符串：\n");
    gets(string);
    printf("字符串的长度是：%ld\n",mystrlen(string));
    return 0;
}
unsigned long mystrlen(const char str[]){
    int i=0;
    unsigned long len=0;
    for(i=0;str[i]!='\0';i++){
        len++;
    }
    return len;
}
//为防止实参被调函数中被修改，可以将形参声明为const类型