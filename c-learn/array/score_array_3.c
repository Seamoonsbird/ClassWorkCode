#include<stdio.h>
int main(){
    int a=1,c=2,b[5]={0},i;
    printf("%p, %p, %p,\n",b,&c,&a);
    for(i=0;i<9;i++){
        b[i]=i;
        printf("%d ",b[i]);
    }
    printf("\nc=%d,a=%d,i=%d\n",c,a,i);
    return 0;
    }
