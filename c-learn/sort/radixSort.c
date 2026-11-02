#include <stdio.h>
#define N 10
void radixSort(int arr[],int n);
int findmax(int arr[],int n);
void countSort(int arr[],int n,int exp);

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

    radixSort(arr,n);

    printf("\n排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void radixSort(int arr[],int n){
    int max=findmax(arr,n);
    for (int exp=1;max/exp>0;exp*=10){
        countSort(arr,n,exp);
    }
}
int findmax(int arr[],int n){
    int max=arr[0];
    for (int i=1;i<n;i++){
        max=arr[i]>max?arr[i]:max;
    }
    return max;
}
void countSort(int arr[],int n,int exp){
    int output[N]={0};
    int count[10]={0};//这里一定要记住初始化，不然后面++操作就会直接加
    for (int i=0;i<n;i++){
        count[arr[i]/exp%10]++;
    }

    for (int i=1;i<10;i++){//这里不能用<=10，因为count[10]越界
        count[i]+=count[i-1];//因为这里有i-1，所以不可以让i从0开始循环
    }

    for (int i=n-1;i>=0;i--){
        int digit=arr[i]/exp%10;
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }
    for (int i=0;i<n;i++){
        arr[i]=output[i];
    }
    
}