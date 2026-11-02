#include <stdio.h>
#include <string.h>
#define MAX_LEN 10
#define N 150
void sortstrings(char *ptr[],int n);
int main(void){
    int i,n;
    char name[N][MAX_LEN];
    char *pStr[N];
    printf("how many contries you want to enter:");
    scanf("%d",&n);
    getchar(); //清除缓冲区的换行符
    printf("enter %d contries name:\n",n);
    for(i=0;i<n;i++){
        pStr[i]=name[i];
        gets(pStr[i]);
    }
    sortstrings(pStr,n);
    printf("the sorted contries name are:\n");
    for(i=0;i<n;i++){
        puts(pStr[i]);
    }
    return 0;
    }
    void sortstrings(char *ptr[],int n){
        int i,j;
        char *temp;//交换的是地址符，要用指针变量
        for(i=0;i<n-1;i++){
            for(j=i+1;j<n;j++){
                if(strcmp(ptr[i],ptr[j])>0){
                    temp=ptr[i];
                    ptr[i]=ptr[j];
                    ptr[j]=temp;
                }
            }
        }
    }