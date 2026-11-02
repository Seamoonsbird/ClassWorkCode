/*
输入一行英文字符串，请统计并输出其中不同单词的数量。

单词由字母组成，大小写不敏感（如 "Hello" 与 "hello" 视为相同）；
单词之间可能由空格或标点隔开；
（1）英文字符串长度不超过300个字符；
（2）每个单词长度不超过 50，且不同单词种类数不超过 100；
请使用指针和字符串函数实现。
【输入描述】

一行，英文文本

【输出描述】

不同单词的数量

【输入示例】

Hello, world! This is a world of hello.
【输出示例】

6
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 300
#define M 100
#define MAX 50
void unpack(char *p,char *str);
int countf(char str[M][N]);
void lowletter(char input[]);
int main(void){
    printf("请输入你要搜索的句子\n");
    char input[N];
    fgets(input,N,stdin);
    input[strcspn(input, "\n")] = '\0';
    lowletter(input);
//    puts(input);
    char str[M][N]={0};
    char *q=str[0];
    unpack(input,q);
    printf("%d",countf(str));

    return 0;
}



void unpack(char *p,char *str){
    int len=strlen(p);
    int word_index=0;
    int j=0;
    for (int i=0;i<len;i++){
//        printf("%c\n",input[i]);
        //遍历每一个字母
        if(isalpha(*(p+i))){
            *(str+word_index*N+j)=*(p+i);
//            printf("%d\n",j);
            j++;
//            printf("%d\n",isalpha(input[i]));
//            printf("\n");
        }
        else{
            if (j>0){
                *(str+word_index*N+j)='\0';
                word_index++;
                j=0;
                //开始下一个单词，j一定要记得初始化
            }
        }
    }
/*  
    for (int i=0;i<word_index;i++){
        printf("%s\n",str[i]);
    }
*/
}

//统计不同单词的数量
int countf(char str[M][N]){
    int count=0;
    for (int i=0;isalpha(str[i][0]);i++){
        int flag=1;
        for (int j=0;j<i;j++){
            if (strcmp(str[i],str[j])==0){
                flag=0;
                break;
            }
        }
        if(flag){
//            printf("%s\n",str[i]);
            count++;
        }
    }
    return count;
}


//将字符串全部转为小写
void lowletter(char input[]){
    for (int i=0;i<strlen(input);i++){
        if(isalpha(input[i])){
            input[i]=tolower(input[i]);
        }
    }
}
