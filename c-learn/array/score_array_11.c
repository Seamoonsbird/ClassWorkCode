//更新日志：该版本加入学号功能
//知识点：键值 
#include<stdio.h>
#define N 40

double AV(int score[],int n);
int SC(int score[],long num[]);
void SORT(int score[],long num[],int n);
void PRINT(int score[],long num[],int n);

int main(){
	 
	
	int score[N];
	int n;
	double av;
	long num[N];//忘记定义为数组了 
	
	n=SC(score,num);
	av=AV(score,n);
	printf("你们班%d人的平均分是%f\n",n,av);
	SORT(score,num,n);
	PRINT(score,num,n);//鬼使神差又将num写成max 
	
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
int SC(int score[],long num[]){
	int i=-1;
	do{
		i++;
		printf("请输入第%d名同学的学号和成绩\n",i+1);//鬼使神差写成n+1 
		scanf("%ld%d",&num[i],&score[i]);
	}while (num[i]>0&&score[i]>0);
	
	return i;
	}

void SORT(int score[],long num[],int n){//不要在括号后面加； 
	int i,j,k,max;
	for(i=0;i<n-1;i++){//注意，数组最后一位为score[n-1],所以此处要用i<n-1 ，而且记得用；不要用， 
		k=i;
		for (j=i+1;j<n;j++){
			if(score[j]>score[k]){
				k=j;
			}
		}
		if (k!=i){
			int t1;
			long t2;
			t1=score[k];
			score[k]=score[i];
			score[i]=t1;
			t2=num[k];
			num[k]=num[i];
			num[i]=t2;
		}
		}
	}
	
	
void PRINT(int score[],long num[],int n){
	int i=0;//又忘记定义i 
	printf("这组学生成绩从高到低为:\n"); 
	for (i=0;i<n;i++){
		printf("\t%ld\t%d\n",num[i],score[i]);
	}
}
