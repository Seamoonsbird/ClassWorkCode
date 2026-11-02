#include <stdio.h>
#include<stdlib.h>
#define N 10
void countSort(int arr[],int n);
int main(void) {
    int arr[N];

    printf("请问有几个整数：\n");
    int n=0;
    scanf("%d",&n);
    printf("请输入%d个整数：\n",n);
    for (int i=0;i<n;i++){
        scanf("%d",arr+i);
    }

    printf("排序前：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    countSort(arr,n);

    printf("\n排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void countSort(int arr[],int n){

    if (n <= 1) return;//增强健壮性

    int i=0;

    int max=arr[0];
    for (i=1;i<n;i++){
        if (arr[i]>max){
            max=arr[i];
        }
    }

    int *countArr=(int *)malloc((max+1)*sizeof(int));
    for (i=0;i<n;i++){
        countArr[arr[i]]++;
    }

    int index=0;
    for (i=0;i<=max;i++){
        while(countArr[i]>0){
            arr[index++]=i;
            countArr[i]--;//注意这里错了，想想为什么
        }
    }
    free(countArr);
}