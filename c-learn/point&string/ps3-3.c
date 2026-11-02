//
#include <stdio.h>
void input(int a[],int n){
    for(int i=0;i<n;i++){
        scanf("%d",a+i);
    }
}
void output(int a[],int n){
    for(int i=0;i<n;i++){
        printf("%4d",*(a+i));
    }
}//形参声明为数组，输入数组元素值，且用指针法访问数组元素
int main(void){
    int a[5],i;
    printf("请输入5个整数：\n");
    input(a,5);
    output(a,5);
    printf("\n");
    return 0;
}