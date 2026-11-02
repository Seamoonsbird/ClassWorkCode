#include <stdio.h>
#define N 10
int partition(int array[],int left,int right);
void quickSort(int array[],int left,int right);
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

    quickSort(arr,0,n-1);

    printf("\n排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

int partition(int array[],int left,int right){
    int pivot =array[left];//直接使用最左边的元素作为基准
    int i=left;
    int j=right;
    while (i<j){
        while (i<j && array[j]>pivot){
            j--;
        }
        while (i<j && array[i]<pivot){
            i++;
        }
        if (i<j){
            int temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
    }
    return i;
}

void quickSort(int array[],int left,int right){
    if (left<right){
        int pivotx=partition(array,left,right);
        quickSort(array,left,pivotx);
        quickSort(array,pivotx+1,right);
    }
}
/*
以数组 [6, 1, 3, 7, 9, 4, 2, 5, 8]（n=9）为例，选「第一个元素 6 作为基准」，演示完整过程：
第 1 步：分区（核心中的核心）
分区目标：把数组分成「左小右大」，基准 6 归位到正确位置。用「双指针法」分区（最常用、最易实现）：
初始化指针：i=left=0（左指针，从左向右找比基准大的元素），j=right=8（右指针，从右向左找比基准小的元素）；
基准值：pivot = arr[left] = 6；
分区过程（循环执行，直到 i>=j）：
右指针 j 向左移：找比 pivot（6）小的元素，直到arr[j] <= pivot → j 停在元素 2（下标 7，arr[7]=2）；
左指针 i 向右移：找比 pivot（6）大的元素，直到arr[i] >= pivot → i 停在元素 7（下标 3，arr[3]=7）；
此时 i=3 < j=7，交换arr[i]和arr[j] → 数组变成 [6,1,3,2,9,4,7,5,8]；
重复 1-3：
j 继续左移，找到元素 5（下标 8？不，arr[8]=8>6，j=7→6→5→4：arr[5]=4<=6，j 停在 5）；
i 继续右移，找到元素 9（下标 4，arr[4]=9>=6，i 停在 4）；
i=4 < j=5，交换arr[4]和arr[5] → 数组变成 [6,1,3,2,4,9,7,5,8]；
重复 1-3：
j 继续左移，j=5→4，此时 i=4 == j=4，循环终止；
把基准 pivot（6）和arr[i]（此时 i=j=4，arr[4]=4）交换 → 基准归位！
最终分区结果：[4,1,3,2,6,9,7,5,8]；
左子数组（比 6 小）：[4,1,3,2]（left=0，right=3）；
右子数组（比 6 大）：[9,7,5,8]（left=5，right=8）；
第 2 步：递归处理左、右子数组
对左子数组[4,1,3,2]重复「选基准（4）+ 分区」→ 分区后变成[2,1,3,4]，再递归处理[2,1,3]和[]（空数组无需处理）；
对右子数组[9,7,5,8]重复「选基准（9）+ 分区」→ 分区后变成[8,7,5,9]，再递归处理[8,7,5]和[]；
第 3 步：递归终止
直到所有子数组都只有 1 个元素（比如[2]、[1]、[3]、[8]、[7]、[5]），递归终止，整个数组有序：[1,2,3,4,5,6,7,8,9]
*/