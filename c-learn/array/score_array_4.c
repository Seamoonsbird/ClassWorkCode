#include<stdio.h>
int main(){
    int array[3][4],i,j;
    printf("请输入数据\n");
    for(i=0;i<3;++i){
        for (j=0;j<4;++j){
        scanf("%d",&array[i][j]);
        }
    }
    printf("数据为\n");
        for(i=0;i<=2;++i){
        for (j=0;j<=3;++j){
        printf("\t%d",array[i][j]);
        }
        printf("\n");

    }
    return 0;
    }
