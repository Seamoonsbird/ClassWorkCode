#include <stdio.h>

int compare_count = 0;   // 比较次数（全局计数器）

// 归并操作：将 arr[left..mid] 和 arr[mid+1..right] 合并到 temp[] 再复制回 arr[]
void merge(int arr[], int temp[], int left, int mid, int right) {

    int i = left;
    int j = mid + 1;
    int k = left;

    // TODO: 归并两段有序区间
    // 需要在每次比较时执行： compare_count++;

    
    // while(i <= mid && j <= right) { ... }
    while(i<=mid&&j<=right){
        if(arr[i]<=arr[j]){
            temp[k++]=arr[i++];
        }
        else {
            temp[k++]=arr[j++];
        }
        compare_count++;

    
    }
    // TODO: 处理剩余元素
    // while (i <= mid) ...
        while(i<=mid){
            temp[k++]=arr[i++];
        }
    // while (j <= right) ...
        while(j<=right){
            temp[k++]=arr[j++];
        }
    // TODO: 将 temp[left..right] 复制回 arr[]
    for (i=left;i<=right;i++){
        arr[i]=temp[i];
    }
}


// 二路归并排序
void mergeSort(int arr[], int temp[], int left, int right) {

    if (left >= right) return;

    int mid = (left + right) / 2;

    // TODO: 对左半区递归
    mergeSort(arr,temp,left,mid);
    // TODO: 对右半区递归
    mergeSort(arr,temp,mid+1,right);
    // TODO: 归并左右两半区
    merge(arr,temp,left,mid,right);
}


int main() {

    int arr[12] = {38, 27, 43, 3, 9, 82, 10, 55, 19, 4, 7, 15};
    int n = 12;
    int temp[12];

    mergeSort(arr, temp, 0, n - 1);

    printf("排序结果：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n比较次数：%d\n", compare_count);

    return 0;
}

