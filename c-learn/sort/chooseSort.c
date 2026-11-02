#include <stdio.h>
void swap(int array[],int i,int j);
void chooseSort(int arr[],int n);
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

    chooseSort(arr,n);

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

void chooseSort(int arr[],int n){
    int k=0;
    for (int i=0;i<n-1;i++){
        k=i;
        for (int j=i+1;j<n;j++){
            if(arr[k]>arr[j]){
                k=j;
            }
        }
        swap(arr,k,i);
    }
}