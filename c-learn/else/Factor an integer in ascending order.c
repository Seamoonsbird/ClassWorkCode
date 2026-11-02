#include <stdio.h>
int main (){
    int x;
    printf("请输入一个正整数：\n");
    scanf("%d",&x);
    int mask=1;
    int t=x;

    while (t>9){
        t/=10;
        mask=mask*10;
    }
    printf("mask=%d t=%d\n",mask,t);
    do{
        int d=x/mask;
        printf("%d",d);
        x=x%mask;
        mask/=10;
        if(mask>0){
            printf(" ");
        }
    }while(mask>0);

    return 0;

}
