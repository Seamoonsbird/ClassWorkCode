//二维数组
#include <stdio.h>
#define N 40
#define COURSE_N 3

void SCAN (int score[N][COURSE_N],long num[N],int n);
void SUMSandAVS(int score[N][COURSE_N],double avs[N],int sums[N],int n);
void SUMCandAVC(int score[][COURSE_N],double avc[COURSE_N],int sumc[COURSE_N],int n);
void PRINT(int score[N][COURSE_N],long num[N],int sums[N],int sumc[COURSE_N],double AVS[N],double AVC[COURSE_N],int n);
int main(void){
    int score[N][COURSE_N];
    int sums[N];
    int sumc[COURSE_N];
    double avs[N];
    double avc[COURSE_N];
    long num[N];
    int i,n;
    printf("请问你们班有多少人？\n");
    scanf("%d",&n);
    SCAN(score,num,n);
    SUMSandAVS(score,avs,sums,n);
    SUMCandAVC(score,avc,sumc,n);
    PRINT(score,num,sums,sumc,avs,avc,n);
    return 0;
}

void SCAN (int score[N][COURSE_N],long num[N],int n){
    int i,j;

    for(i=0;i<n;i++){
        printf("请输入第%d个学生的学号，各科成绩\n",i+1);
        scanf("%ld",&num[i]);
        for(j=0;j<COURSE_N;j++){
            scanf("%d",&score[i][j]);
        }
    }
}

void SUMSandAVS(int score[N][COURSE_N],double avs[N],int sums[N],int n){
    int i,j;
    for(i=0;i<n;i++){
        sums[i]=0;//一定要记得初始化,不要写int SUMS[i]=0;
        for(j=0;j<COURSE_N;j++){
            sums[i]+=score[i][j];
        }
        avs[i]=sums[i]/COURSE_N;
    }
}

void SUMCandAVC(int score[][COURSE_N],double avc[COURSE_N],int sumc[COURSE_N],int n){
    int i,j;
    for(j=0;j<COURSE_N;j++){
        sumc[j]=0;
        for(i=0;i<n;i++){
            sumc[j]+=score[i][j];
        }
        avc[j]=sumc[j]/n;
    }

}

void PRINT(int score[N][COURSE_N],long num[N],int sums[N],int sumc[COURSE_N],double avs[N],double avc[COURSE_N],int n){//这一行的avs和avc不能大写，因为函数中用的是和这个一样的，都要是小写
    int i,j;
    printf("这组学生的成绩整理如下:\n学号\t语文\t数学\t英语\t总分\t平均分\t\n");
    for(i=0;i<n;i++){
        printf("%ld\t",num[i]);
        for(j=0;j<COURSE_N;j++){
            printf("%d\t",score[i][j]);
        }
        printf("%d\t%f\t\n",sums[i],avs[i]);
    }
    printf("的总分：\t");
    for(j=0;j<COURSE_N;j++){
        printf("%4d\t",sumc[j]);
    }
    printf("\n平均分：\t");
    for(j=0;j<COURSE_N;j++){
        printf("%4.1f\t",avc[j]);
    }
}