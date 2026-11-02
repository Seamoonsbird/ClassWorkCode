//ps4为指针与二维数组
//此版为用数组的原版
#include <stdio.h>
#define N 4
void input(int p[][N],int m,int n);
void output(int p[][N],int m,int n);
int main(void){
    int a[3][4];
    printf("请输入3*4矩阵：\n");
    input(a,3,4);
    output(a,3,4);
    return 0;
}
void input(int p[][N],int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&p[i][j]);
        }
    }
}
void output(int p[][N],int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%4d",p[i][j]);
        }
        printf("\n");
    }
}