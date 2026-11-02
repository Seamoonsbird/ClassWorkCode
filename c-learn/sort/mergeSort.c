#include <stdio.h>
#define N 10
void merge(int array[],int left,int mid,int right);
void mergeSort(int array[],int laft,int right);
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

//关键就是怎么一分为二，因为大部分数组都不会是2的次方
//不用管，除2就行

    mergeSort(arr,0,n-1);

    printf("排序后的结果为：\n");
    for (i=0;i<n;i++){
        printf("\t%d",*(arr+i));
    }
    printf("\n");
    
    return 0;
}



void mergeSort(int array[],int left,int right){
    if(left<right){
        int mid=left+(right-left)/2;
        mergeSort(array,left,mid);
        mergeSort(array,mid+1,right);
        merge(array,left,mid,right);
    }
}
/*
用了递归思想，分两半排好序，两半中的一半又分为两半
*/
void merge(int array[],int left,int mid,int right){
    int temp[N];
    int i=left;
    int j=mid+1;
    int k=left;
    while(i<=mid&&j<=right){
        if (array[i]<=array[j]){
            temp[k++]=array[i++];
            //为什么这里要用一个k和一个i两个看似重复的东西来标记呢
            //是因为i++之后，i的值会改变，这时候就不可以再用temp[i++]了
            //而且，又不一定是合并一个数组里面的，请看下面
        }
        else{
            temp[k++]=array[j++];
        }
        
    }
    while (i<=mid){
        temp[k++]=array[i++];
    }
    while (j<=right){
        temp[k++]=array[j++];
    }
    /*
    这两个while循环其实不是同时都要执行的，只能有一个while执行，所以不必担心
    */
    for (k=left;k<=right;k++){
        array[k]=temp[k];
    }
    /*
    咋把这两个while和一个for搞进了一个while里面呢*/
}