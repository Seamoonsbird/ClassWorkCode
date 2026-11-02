#include <stdio.h>
#define N 100
typedef struct stack {
    char data[N];
    int top;
}stack;

void push(char a,stack *c);
char pop(stack *c);
int is_empty(stack *c);
void initstack(stack *c);
void delete_line(stack *c);
void delete_char(stack *c);


int main(void){
    stack str1;
    stack str2;
    initstack(&str1);
    initstack(&str2);
    char ch;
    printf("请输入文本\n");
    while ((ch=getchar())!='\n'){
        switch (ch)
        {
        case '@':
            delete_line(&str1);
            break;
        case '#':
            delete_char(&str1);
            break;
        default:
            push(ch,&str1);
            break;
        }
    }
    push('\0',&str1);
    int i=0;
    while(str1.data[i]!='\0'){
        printf("%c",str1.data[i]);
        i++;
    }
    return 0;
}


void push(char a,stack *c){
    c->data[c->top]=a;
    c->top++;
}
char pop(stack *c){
    c->top--;
    return c->data[c->top];
}
void initstack(stack *c){
    c->top=0;
}
int is_empty(stack *c){
    return c->top==0;
}
void delete_line(stack *c){
    while (!is_empty(c)){
        c->top--;
        c->data[c->top]='\0';
    }
}
void delete_char(stack *c){
    c->top--;
    c->data[c->top]='\0';
}