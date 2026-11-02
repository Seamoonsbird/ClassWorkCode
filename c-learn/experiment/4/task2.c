#include <stdio.h>
#include <stdlib.h>

int maxDiff(int nums[],int a,int b);
int max(int a,int b);
int main(void){
    printf("请输入数组长度：");
    int n=0;
    scanf("%d",&n);
    printf("请输入数组内容：\n");
    int *nums=NULL;
    nums=(int *)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    if(maxDiff(nums,0,n-1)>=0){
        printf("true\n");
    }
    else {
        printf("false\n");
    }
    return 0;
}

int max(int a,int b){
    return a>b?a:b;
}

int maxDiff(int nums[],int a,int b){
    if (a==b){
        return nums[a];
    }
    else if (a!=b){
        max(nums[a]-maxDiff(nums,a+1,b),nums[b]-maxDiff(nums,a,b-1));
    }
    
}