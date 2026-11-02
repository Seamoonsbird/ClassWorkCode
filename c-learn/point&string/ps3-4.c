//
#include <stdio.h>
void input(int *p,int n){
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
    }
}
void output(int *p,int n){
    for(int i=0;i<n;i++){
        printf("%4d",p[i]);
    }
}//形参声明为指针变量，输入数组元素值，且用下标法访问数组元素
int main(void){
    int a[5],i;
    printf("请输入5个整数：\n");
    input(a,5);
    output(a,5);
    printf("\n");
    return 0;
}
//注意，在主函数中没有必要用指针变量作为函数实参