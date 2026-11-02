//输入某班学生某门课的成绩（最多不超过40人），当输入为负值时，表示输入结束，
// 用函数编程统计成绩高于平均分的学生人数。
#include <stdio.h>
#define N 40
int ReadScores(int scores[]);
double average(int scores[],int n);
int count(int aver,int scores[],int n);
int main(void){
    int scores[N];
    int n=ReadScores(scores);
    int aver=average(scores,n);
    int nums=count(aver,scores,n);
    printf("平均分为：%d\n",aver);
    printf("高于平均分的学生人数为：%d\n",nums);
    return 0;
}
int ReadScores(int scores[]){
    int i=0;
    do{
        printf("请输入第%d个学生的成绩：\n",i+1);
        scanf("%d",scores+i);
    }while(scores[i]>=0&&++i<N);
    return i;
}

double average(int scores[],int n){
    int sum=0;
    for (int i=0;i<n;i++){
        sum+=scores[i];
    }
    double aver=(double)sum/n;
    return aver;
}

int count(int aver,int scores[],int n){
    int count=0;
    for (int i=0;i<n;i++){
        if (scores[i]>aver){
            count++;
        }
    }
    return count;
}