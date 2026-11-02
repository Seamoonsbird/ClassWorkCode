#include <stdio.h>
#define N 100
typedef struct stack{
    char data[N];
    int top;
}stack;
void initstack(stack *str);
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
        ch=getchar();
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