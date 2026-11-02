#include <stdio.h>
# define N 80
void mystrcpy(char dststr[],char srcstr[]);
int main(void){
    char a[N],b[N];
    printf("请输入字符串a：\n");
    gets(a);
    mystrcpy(b,a);
    printf("字符串b的内容是：\n");
    puts(b);
    return 0;
}
void mystrcpy(char dststr[],char srcstr[]){
    int i=0;
    while(srcstr[i]!='\0'){
        dststr[i]=srcstr[i];
        i++;
    }
    dststr[i]='\0';
}