/*利用下面提供的函数 Swap()，按如下函数原型编程计算并输出 n×n 阶矩阵的转置矩阵。其中，n 由用户从键盘输入。已知 n 值不超过 10。
void Transpose(int a[][N], int n);

void Swap(int *x, int *y)
{
int temp;
temp = *x;
*x = *y;
*y = temp;
}
*/
#include <stdio.h>
#define N 10
void Swap(int *x, int *y)
{
int temp;
temp = *x;
*x = *y;
*y = temp;
}
int main(void){
    int n=0;
    printf("请输入矩阵的阶数n（n不超过10）：\n");
    scanf("%d",&n);
    int a[N][N];
    int i=0,j=0;
    for (i=0;i<n;i++){
            printf("请输入矩阵第%d行的元素：\n",i+1);
        for (j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for (i=0;i<n;i++){
        for (j=i+1;j<n;j++){
            Swap(&a[i][j],&a[j][i]);
        }
    }
    printf("转置后的矩阵为：\n");
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("\t%d",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}