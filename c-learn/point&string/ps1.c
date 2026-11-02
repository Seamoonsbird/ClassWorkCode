//用下标法引用数组元素
#include <stdio.h>
int main(void){
    int a[5],i;
    printf("请输入5个整数：\n");
    for(i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<5;i++){
        printf("%d",a[i]);
    }
    printf("\n");
    return 0;
}