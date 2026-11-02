/*
使用一维数组实现两个正整数相加，输出它们的和。
注意：两个加数的位数不一定相等
【输入描述】
两行，分别是两个正整数
位数最少为20位，不超过50位
【输出描述】
两个正整数的和
【输入示例】
123456789341341234567
 11135439503091234567
【输出示例】
134592228844432469134
*/
#include <stdio.h>
#include <string.h>
void reverse(char str[]);
int main(void){
    char str[2][51];
    printf("请输入数字1\n");
    scanf("%s",str[0]);
    printf("请输入数字2\n");
    scanf("%s",str[1]);

    //反转字符串，方便从低位开始相加
    reverse(str[0]);
    reverse(str[1]);
    char result[51]={0};
    int digit_result[51]={0};
    for (int i=0;i<strlen(str[0])||i<strlen(str[1]);i++){
        int digit1=(i<strlen(str[0]))?(str[0][i]-'0'):0;//这里出错误，如果是空的，就是0，那么他的ASCII值是0，不是'0'的48
        int digit2=(i<strlen(str[1]))?(str[1][i]-'0'):0;

        digit_result[i]+=(digit1+digit2)%10;
        //处理进位
        if((digit1+digit2)/10>0){
            digit_result[i+1]+=(digit1+digit2)/10;
            result[i+1]=digit_result[i+1]+'0';
        }
        
        result[i]=digit_result[i]+'0';
    }
    reverse(result);
    printf("%s",result);
    return 0;
}

void reverse(char str[]){
    char *p=str;
    char *q=str+strlen(str)-1;
    char temp=0;
    while (p<q){
        temp=*q;
        *q=*p;
        *p=temp;
        p++;
        q--;
    }
}