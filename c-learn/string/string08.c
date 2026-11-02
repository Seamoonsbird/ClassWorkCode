#include <stdio.h>
#include <string.h>
#define N 150
#define MAX 10
void sortstring(char str[][MAX],int n);
int main(void){
    int i,n;
    char name[N][MAX];
    printf("请输入国家总数量：\n");
    scanf("%d",&n);
    getchar();
    printf("请输入国家名称：\n");
    for(i=0;i<n;i++){
        gets(name[i]);
    }
    sortstring(name,n);
    printf("排序后的国家名字:\n");
    for(i=0;i<n;i++){
        puts(name[i]);
    }
    return 0;
}
void sortstring(char str[][MAX],int n){
    int i,j;
    char t[MAX];
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(str[i],str[j])>0){//该函数用于比较两个字符串的大小，从第一个不同的字符开始比较，若前者大于后者则返回正值，若小于则返回负值，若相等则返回0
                strcpy(t,str[i]);//字符串赋值只能使用strcpy函数
                strcpy(str[i],str[j]);
                strcpy(str[j],t);
            }
        }
    }
}