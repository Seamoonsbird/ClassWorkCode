/*
题目描述
实现一个基于数组或链表的字符栈（Stack）。编写主程序，接收用户输入的一个字符串，利用栈的特性将其逆序打印出来。
核心要求
1.	定义包含数据域和栈顶指针的栈结构体。
2.	实现栈的push（入栈）和pop（出栈）操作函数。
3.	将输入字符串的字符依次入栈，全部入栈后循环弹出并打印栈顶元素至栈空。
*/
#include <stdio.h>
#define N 100
typedef struct stack{
    char data[N];
    int top;
}stack;
void initstack(stack *str);//C语言中不能在结构体中赋初值，必须在写一个函数来完成
void push(char c,stack *str);
char pop(stack *str);
int isEmpty(stack *str);
int main(void){
    stack str;
    initstack(&str);
    printf("请输入你要倒序的字符\n");
    char ch=getchar();
    while (ch!='\n'){
        push(ch,&str);
        ch=getchar();//这里不能写char ch=getchar();
    }
    while (!isEmpty(&str)){
        putchar(pop(&str));
    }
    return 0;
}

void push(char ch,stack *str){
    str->data[str->top]=ch;
    str->top++;
}

char pop(stack *str){
    str->top--;
    char ch=str->data[str->top];
}
int isEmpty(stack *str){
    return str->top==0;
}
void initstack(stack *str){
    str->top=0;
}