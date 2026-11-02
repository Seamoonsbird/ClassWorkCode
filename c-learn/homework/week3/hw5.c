//任意输入英文的星期几,通过查找如下图中所示的星期表,输出其对应的数字。
// 若查到表尾,仍未找到,则输出错误提示信息。
#include <stdio.h>
#include <string.h>
#define N 7

int main(void){
    char day[10];
    char str[N][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    printf("请输入星期几的英文单词：\n");
    gets(day);
    for (int i=0;i<N;i++){
        if (strcmp(day,str[i])==0){
            printf("%s对应的数字是：%d\n",day,i);
            return 0;
        }
    }
    printf("非法输入\n");
    return 0;
}