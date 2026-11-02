/*
n(n≤100)名同学参加歌唱比赛，并接受 m(m≤20)名评委的评分，评分范围是 0到 10分。
这名同学的得分就是这些评委给分中去掉一个最高分，去掉一个最低分，剩下 m-2 个评分的平均数。
请问得分最高的同学分数是多少？评分保留 2 位小数。
*/
#include <stdio.h>
#include <stdlib.h>
#define JudgeNum 20
//#define StudentNum 100
typedef struct student{
    int score[JudgeNum];
    double aver;
}student;
double find(double arr[],int n,int (*compare)(double a,double b));
int Max(double a,double b);
int Min(double a,double b);
double aver(int arr[],int n);
void readScore(int n,int m,student *p);
int main(void){
//    printf("请输入学生和评委的数量：\n");
    int n=0;
    int m=0;
    scanf("%d %d",&n,&m);
    student *data=NULL;
    data=(student *)malloc(n*sizeof(student));
    if(data==NULL){
        printf("memory allocation failed\n");
        exit(1);
    }
    readScore(n,m,data);
    double *average=NULL;
    average=(double *)malloc(n*sizeof(double));
    if(average==NULL){
        printf("memory allocation failed\n");
        exit(1);
    }
    for(int i=0;i<n;i++){
        average[i]=aver(data[i].score,m);
    }
    double score_max=find(average,n,Max);
//    printf("最高分同学的分数为：");
    printf("%.2lf\n",score_max);
    free(data);
    free(average);
    return 0;
}
double find(double arr[],int n,int (*compare)(double a,double b)){
    double result=arr[0];
    for(int i=1;i<n;i++){
        if (compare(arr[i],result)){
            result=arr[i];
        }
    }
    return result;
}

int Max(double a,double b){
    return a>b;
}
int Min(double a,double b){
    return a<b;
}
double aver(int arr[],int m){
    double aver=0;
    double sum=0;
    for(int i=0;i<m;i++){
        sum+=arr[i];
    }
    double temp_arr[m];
    for(int i=0;i<m;i++){
        temp_arr[i] = (double)arr[i]; // 显式转换每个分数为double
    }
//为什么要一个一个转换呢，因为强制数据类型转换只能针对一个数据，不能转数组
/*
而且，因为我用的是malloc，find 函数会按 double 的 8 字节规则读取内存。
相当于把多个 int 值 “拼接” 成错误的 double 值（比如 int 数组 [4,7,2,6] 会被解析成一个超大的错误 double 数）。
*/
    sum-=(find(temp_arr,m,Max)+find(temp_arr,m,Min));
    aver=sum/(m-2);
    return aver;
}
void readScore(int n,int m,student *p){
    for (int i=0;i<n;i++){
//        printf("请输入第%d个学生的数据：\n",i+1);
        for (int j=0;j<m;j++){
            scanf("%d",&p[i].score[j]);
        }
    }
}
/*
task1.c: In function ‘main’:
task1.c:32:19: warning: passing argument 3 of ‘readScore’ from incompatible pointer type [-Wincompatible-pointer-types]
   32 |     readScore(n,m,&data);
      |                   ^~~~~
      |                   |
      |                   student **
task1.c:20:37: note: expected ‘student *’ but argument is of type ‘student **’
   20 | void readScore(int n,int m,student *p);
      |                            ~~~~~~~~~^
*/