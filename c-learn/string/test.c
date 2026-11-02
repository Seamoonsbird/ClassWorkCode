#include <stdio.h>
int main(void){
    char str[10];
    printf("请输入一个字符串，不超过10个字符：\n");
    scanf("%s",str);
    printf("%d\n",*str);//突发奇想，打印字符串首字符的ASCII码值
    printf("%d\n",*(str+1));
    printf("%d\n",*(str+2));
    return 0;
}