#include<stdio.h>
#define N 40
int main(){
	double AV(int score[],int n);
	int SC(int score[]);
	int score[N];
	int n;
	double av;
	
	n=SC(score);
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
int SC(int score[]){
	int i=-1;
	do{
		i++;
		printf("请输入这名同学的成绩\n");
		scanf("%d",&score[i]);
	}while (score[i]>0);
	
	return i;
	}
