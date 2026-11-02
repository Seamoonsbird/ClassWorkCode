#include <stdio.h>
#include <stdlib.h>

#define N 10
int min(int x, int y);
void merge_sort(int arr[], int len) ;

int main(void){
    int i=0,j=1;
    int arr[N];

    printf("请问有几个整数：\n");
    int n=0;
    scanf("%d",&n);
    printf("请输入%d个整数：\n",n);
    for (i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("\n");

    merge_sort(arr,n);

    printf("排序后的结果为：\n");
    for (i=0;i<n;i++){
        printf("\t%d",*(arr+i));
    }
    printf("\n");
    
    return 0;
}

int min(int x, int y) {
    return x < y ? x : y;
}
void merge_sort(int arr[], int len) {
    int *a = arr;
    int *b = (int *) malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg * 2) {
            int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

/*
网上找的另一种算法，这不是自顶向下拆分数组，而是自底向上合并数组，因此不用递归*/

