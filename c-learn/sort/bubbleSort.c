#include <stdio.h>
void swap(int array[],int i,int j);
void bubbleSort(int arr[],int n);
int main(void){
    int i=0,j=1;
    int arr[10];

    printf("请问有几个整数：\n");
    int n=0;
    scanf("%d",&n);
    printf("请输入%d个整数：\n",n);
    for (i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("\n");

    printf("排序前的结果为：\n");
    for (i=0;i<n;i++){
        printf("\t%d",*(arr+i));
    }
    printf("\n");

    bubbleSort(arr,n);

    printf("排序后的结果为：\n");
    for (i=0;i<n;i++){
        printf("\t%d",*(arr+i));
    }
    printf("\n");
    
    return 0;
}

void swap(int array[],int i,int j){
    int temp;
    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}
void bubbleSort(int arr[],int n){
    for (int i=0;i<n;i++){
        int flag=1;
        for (int j=0;j<n-i-1;j++){
            if (arr[j]>arr[j+1]){//避免 j 达到 n-1 时，j+1 越界（j 最大只能到 n-i-2，j+1 = n-i-1，刚好是当前轮次的最后一个有效元素）。
                swap(arr,j,j+1);
                flag=0;
            }
        }
        if (flag){
            break;
        }
    }
}
/*
seamoonsbird@LAPTOP-B2V66C3M ~/m/sort (main)> ./bin/bubbleSort
请问有几个整数：
5
请输入5个整数：
1 
 4
8
5
7

排序前的结果为：
        1       4       8       5       7
排序后的结果为：
        0       1       4       5       7*/