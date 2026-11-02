#include <stdio.h>
#define N 100
typedef struct stack {
    char data[N];
    int top;
}stack;
void initstack(stack *c){
    c->top=0;
}
void push(char a,stack *c);
char pop(stack *c);
int is_empty(stack *c);
int main(void){
    stack c;
    initstack(&c);
    char ch;
    printf ("请输入括号，如果不想输了就输入#\n");
    while((ch =getchar())!='#'){
        switch(ch){
            case '(':
            case '[':
            case '{':
                push(ch,&c);break;
            case ')':
                if (is_empty(&c)){
                    printf("FALSE\n");
                    return 0;
                }
                else{
                if (pop(&c)!='('){
                    printf("FALSE\n");
                    return 0;
                }
                else {
//                    pop(&c);前面判断的时候已经调用了一遍函数
                    break;
                }
                }
            case ']':
            if (is_empty(&c)){
                printf("FALSE\n");
                return 0;
            }else{
                if (pop(&c)!='['){
                    printf("FALSE\n");
                    return 0;
                }
                else {
                    break;
                }
            }
            case '}':
            if (is_empty(&c)){
                printf("FALSE\n");
                return 0;
            }else{
                if (pop(&c)!='{'){
                    printf("FALSE\n");
                    return 0;
                }
                else {
                    break;
                }
            }
            default:
            break;
        }
    }
    if(is_empty(&c)){
        printf("TRUE\n");
    }
    else{
        printf("FALSE\n");
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
int is_empty(stack *c){
    return c->top==0;
}
