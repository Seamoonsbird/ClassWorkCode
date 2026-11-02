#include <stdio.h>
int main(){
    int score[5];
    int totalScore=0;
    int averageScore=0;
    int i=0;//忘记这一步
    printf("请输入每位同学的成绩：\n");
    for(i=0;i<5;i++){
        scanf("%d",&score[i]);
        totalScore+=score[i];
    }//忘记for里面是要用;而不是,！
    averageScore=totalScore/5.0;
    printf("这五位学生的平均成绩是%d\n",averageScore);

    return 0;
}
