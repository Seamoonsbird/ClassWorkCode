#include <stdio.h>
unsigned long mystrlen(const char *pstr);
int main(void){
    int i;
    char string[80];
    printf("请输入一个字符串：\n");
    gets(string);
    printf("字符串的长度是：%ld\n",mystrlen(string));
    return 0;
}
unsigned long mystrlen(const char *pstr){
    int i=0;
    unsigned long len=0;
    for(i=0;*pstr!='\0';pstr++){
        len++;
    }
    return len;
}