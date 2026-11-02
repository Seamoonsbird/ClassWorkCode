//此版本用了函数指针实现升序降序选择，减少代码重复
#include <stdio.h>
#define N 40
void READSCORE(int score[],long num[],int n);
void PRINT(int score[],long num[],int n);
void SWAP(int *a,int *b,long *c,long *d);
void SELECTIONSORT(int score[],long num[],int n,int(*compare)(int a,int b));
int Asending(int a,int b);
int Dsending(int a,int b);
int main(void){
    int score[N];
    long num[N];
    int n;
    printf("请问你们班有多少人？\n");
    scanf("%d",&n);
    READSCORE(score,num,n);
    printf("请问你想要升序还是降序，升序的扣1，降序的扣2\n");
    int haipeng=0;
    scanf("%d",&haipeng);
    if(haipeng==1){
        SELECTIONSORT(score,num,n,Asending);
        PRINT(score,num,n);
    }
    else if(haipeng==2){
         SELECTIONSORT(score,num,n,Dsending);
        PRINT(score,num,n);
    }
    else{
        printf("输入有误\n");
    }
}

void READSCORE(int score[],long num[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("请输入第%d位学生的学号及成绩，以空格隔开\n",i+1);
        scanf("%ld %d",&num[i],&score[i]);
    }
}

void PRINT(int score[],long num[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("学号：%ld\t成绩：%d\t\n",num[i],score[i]);
    }
}

int Asending(int a,int b){
    return a<b;
}
int Dsending(int a,int b){
    return a<b;
}

void SELECTIONSORT(int score[],long num[],int n,int(*compare)(int a,int b)){
    int i,k,j;
    for(i=0;i<n-1;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(compare(score[j],score[k])){
                k=j;
            }
        }
        if(k!=i){
            SWAP(&score[i],&score[k],&num[i],&num[k]);
        }
    }
}

void SWAP(int *a,int *b,long *c,long *d){
    int t1;
    long t2;
    t1=*a;
    *a=*b;
    *b=t1;
    t2=*c;
    *c=*d;
    *d=t2;
}