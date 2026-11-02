#include <stdio.h>
#define N 80
char *mystrat(char *str1,const char *str2);
int main(){
    char str1[2*N];
    char str2[N];
    printf("请输入第一个字符串：\n");
    gets(str1);
    printf("请输入第二个字符串：\n");
    gets(str2);
    printf("连接后的字符串是：\n%s\n",mystrat(str1,str2));
    return 0;
}
char *mystrat(char *str1,const char *str2){
    char *pstr=str1;
    while(*str1!='\0'){
        str1++;
    }
    *str1=' ';
    str1++;
    while(*str2!='\0'){
        *str1=*str2;
        str1++;
        str2++;
    }
    *str1='\0';//一定要加这个
    return pstr;
}
//pstr只是用来装地址，最后返回这个地址即可，不要把数据传进这里面