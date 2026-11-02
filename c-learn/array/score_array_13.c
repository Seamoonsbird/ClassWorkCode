//更新日志：该版本输入学号查找成绩 注：此小版本为折半查找 知识点：查找
#include<stdio.h>
#define N 40
int main(){
	double AV(int score[],int n);
	int SC(int score[],long num[]);
	void SORT1(int score[],long num[],int n);
	void SORT2(int score[],long num[],int n);
	void PRINT(int score[],long num[],int n); 
	int SEARCH(long num[],int n);//long x是用来存要查询的学号的， int num是用来给循环用的，还有只需要将num[]传进去就可以了，不用传成绩，因为输出的可以是该学生的标号i 
	
	int score[N];
	int n;
	double av;
	long num[N];//忘记定义为数组了 
	char a;
	
	n=SC(score,num);
	av=AV(score,n);
	printf("你们班%d人的平均分是%f\n",n,av);
	SORT1(score,num,n);
	PRINT(score,num,n);//鬼使神差又将num写成max 
	printf("请问你要不要查询某同学的成绩?[Y/n]\n"); 
	do{
		// 清理缓冲区残留的字符（包括 '\n'）
    	int temp;
    	while ((temp = getchar()) != '\n' && temp != EOF) {
        // 什么都不做，只是消耗掉残留字符
    	}
		scanf("%c",&a);
		if(a=='Y'||a=='y'||a=='\n'){
			int k;
			SORT2(score,num,n);
			PRINT(score,num,n);
			k=SEARCH(num,n);
			if(k==-1){
				printf("您查找的学号不存在\n");
			} else{
			printf("您要查找的这位同学的成绩为:%d\n",score[k]);//score是d，不是ld 
		}
		}else if(a=='N'||a=='n'){
			break;
		} else{
			printf("服了，不审题，乱输入！\n");
		}
		printf("请问你还要不要查询某同学的成绩?[Y/n]\n"); 
	}while(1);
	return 0;
}

/*
///豆包给的优化，还挺好 
// 先封装一个清理缓冲区的函数，避免重复代码
void clearBuffer() {
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF);
}

do {
    clearBuffer();  // 调用封装的清理函数，代码更简洁
    printf("请问你要不要查询某同学的成绩?[Y/n]\n");  // 提示提前，逻辑更顺
    char a = getchar();  // 用getchar直接读字符，比scanf更直观

    switch (a) {  // 用switch替代if-else，字符判断更清晰
        case 'Y':
        case 'y': {  // 用大括号隔离局部变量
            int k = SEARCH(num, n);
            if (k != -1) {  // 增加未找到的判断，避免数组越界
                printf("您要查找的这位同学的成绩为: %d\n", score[k]);
            } else {
                printf("未找到该学号的同学\n");
            }
            break;  // 处理完查询后跳出switch
        }
        case 'N':
        case 'n':
            printf("退出查询\n");
            goto exitLoop;  // 直接跳出自循环，避免多层break
        default:
            printf("输入错误，请输入 Y/y 或 N/n\n");  // 提示更友好
            goto exitLoop;  // 错误输入直接退出
    }
} while (1);  // 循环条件简化，靠内部逻辑控制退出

exitLoop:  // 标记循环出口
*/
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

void SORT1(int score[],long num[],int n){//不要在括号后面加； 
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

void SORT2(int score[],long num[],int n){//不要在括号后面加； 
	int i,j,k,max;
	for(i=0;i<n-1;i++){//注意，数组最后一位为score[n-1],所以此处要用i<n-1 ，而且记得用；不要用， 
		k=i;
		for (j=i+1;j<n;j++){
			if(num[j]<num[k]){
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
	printf("这组学生成绩为:\n"); 
	for (i=0;i<n;i++){
		printf("\t%ld\t%d\n",num[i],score[i]);
	}
}

int SEARCH(long num[],int n){
//	int n;传进来的数不用再定义
	long x; 
	printf("请输入要查询的学号：\n");
	scanf("%ld",&x);
//	int find=0;注释掉的原因详见下面 
	int low=0,high=n-1;
	while(high>=low){//一定要用>=，找不到就再进一轮循环，就可以退出了，不然找不到学号的时候就会进死循环 
//还有，不要用while (high-1!=low,可读性降低） 
	int mid=low+(high-low)/2;
		if(x<num[mid]){
			high=mid-1;
		}else if(x>num[mid]){
			low=mid+1;
		}else{
//			find=1;下面有return，所以find不等于1也能退出程序，而刚好程序修改前只有这里用到find，现在就更不用了 
			return mid;
		}
	} 
	return -1;
}
