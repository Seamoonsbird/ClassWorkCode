#include <stdio.h>
#include <stdlib.h>
void input(int n,int *p);
double average(int n,int *p);
int main(void){
    int i,n;
    int *p=NULL;
    printf("how many scores you want to enter:");
    scanf("%d",&n);
    p=(int *)malloc(n*sizeof(int));//主动申请内存放在堆里面
    if(p==NULL){
        printf("memory allocation failed\n");
        exit(1);
    }//一定要判断有没有成功申请到
    printf("enter %d scores:\n",n);
    input(n,p);
    printf("the average score is: %.2f\n",average(n,p));
    free(p);//一定要释放内存
    return 0;
}
void input(int n,int *p){
    int i;
    for(i=0;i<n;i++){
        scanf("%d",p+i);
    }
}
double average(int n,int *p){
    int i,sum=0;
    for(i=0;i<n;i++){
        sum+=*(p+i);
    }
    return (double)sum/n;
}