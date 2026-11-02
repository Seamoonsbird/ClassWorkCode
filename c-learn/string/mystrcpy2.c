#include <stdio.h>
# define N 80
void mystrcpy(char *dststr,char *srcstr);
int main(void){
    char a[N],b[N];
    printf("请输入字符串a：\n");
    gets(a);
    mystrcpy(b,a);
    printf("字符串b的内容是：\n");
    puts(b);
    return 0;
}
void mystrcpy(char *dststr,char *srcstr){
    while(*srcstr!='\0'){
        *dststr=*srcstr;
        srcstr++;
        dststr++;
    }
    *dststr='\0';
}