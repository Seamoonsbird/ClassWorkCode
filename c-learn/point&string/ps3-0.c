//指针的下标表示形式
#include <stdio.h>
int main(void){
    int a[5],*p=NULL,i;
    printf("请输入5个整数：\n");
    p=a; //指针指向数组首元素
    for(i=0;i<5;i++){
        scanf("%d",&p[i]);
    }
    for(i=0;i<5;i++){
        printf("%4d",p[i]);
    }
    printf("\n");
    return 0;
}