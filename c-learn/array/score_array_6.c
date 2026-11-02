#include<stdio.h>
#define N 40
int main(){
	double AV(int score[],int n);
	void SC(int score[],int n);
	int score[N];
	int n;
	double av;
	printf("请问你们班有多少人？\n");
	scanf("%d",&n);
	SC(score,n);
	av=AV(score,n);
	printf("你们班%d人的平均分是%f\n",n,av);
	
	return 0;
}
double AV(int score[],int n){//记得这也要加double 
	int i=0;
	double sum=0.0;
	for (i=0;i<n;i++){
		sum+=score[i];
	}
	return n>0 ? sum/n:-1;
}
void SC(int score[],int n){
	int i=0;
	printf("请输入这%d名同学的成绩\n",n);
	for (i=0;i<n;i++){
		scanf("%d",&score[i]);
	}
}
