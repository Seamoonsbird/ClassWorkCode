#include <stdio.h>
#define N 10
void shellSort(int array[],int n);
int main(void) {
    int arr[N];

    printf("请问有几个整数：\n");
    int n=0;
    scanf("%d",&n);
    printf("请输入%d个整数：\n",n);
    for (int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("\n");

    printf("排序前：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    shellSort(arr, n);  // 调用希尔排序

    printf("\n排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void shellSort(int array[],int n){
    for (int gap=n/2;gap>0;gap/=2){
        for (int i=gap;i<n;i++){
            int temp=array[i];
            if (array[i-gap]>temp){
                array[i]=array[i-gap];
                array[i-gap]=temp;
            }
        }
    }
}