#include <stdio.h>
#define N 40
void FINDMAX(int score[],long num[],int *pmaxscore,long *pmaxnum,int n);
void READSCORE(int score[],long num[],int n);

int main(void){
    int n;
    int score[N];
    long num[N];
    int maxscore;
    long maxnum;
    int *pmaxscore=&maxscore;
    long *pmaxnum=&maxnum;
    printf("你们班一共有几位学生:\n");
    scanf("%d",&n);
    READSCORE(score,num,n);
    FINDMAX(score,num,pmaxscore,pmaxnum,n);
    printf("最高分为%ld同学，成绩为%d分\n",maxnum,maxscore);
    return 0;
}
void READSCORE(int score[],long num[],int n){
    int i;
    for (i=0;i<n;i++){
        printf("请输入第%d位学生的学号和分数:\n",i+1);
        scanf("%ld %d",&num[i],&score[i]);
    }
}

void FINDMAX(int score[],long num[],int *pmaxscore,long *pmaxnum,int n){
    int i;
    *pmaxscore=score[0];
    *pmaxnum=num[0];
    for(i=1;i<n;i++){
        if(score[i]>*pmaxscore){
            *pmaxscore=score[i];
            *pmaxnum=num[i];
        }
    }
}