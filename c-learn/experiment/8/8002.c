#include <stdio.h>
#include <stdlib.h>
typedef struct heap{
    int data;
    int index;
}heap;
// 函数原型声明(函数的具体实现需要你在文件末尾完成)
void find_top_k_index(int *interest, int n, int k, int *top_k_index);
void heapAdjust(heap arr[],int n,int i);

void initheap(heap *interest);
int main() {
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    int top_k_index[100];  // 其长度固定为 100，但实际上只需将返回结果写入到其前 k 个元素即可
    find_top_k_index(interest, n, k, top_k_index);
    for (int i = 0; i < k; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", top_k_index[i]);
    }
    printf("\n");
    return 0;
}

// 你需要实现的函数
void find_top_k_index(int *interest, int n, int k, int *top_k_index) {
    // 请将返回结果写入到 top_k_index 数组中
    // 其长度固定为 100，但实际上只需将返回结果写入到其前 k 个元素即可

    // 请在此处编写代码
    
    //建立临时堆并进行初始化
    heap temp_arr[100];
    for (int i=0;i<k;i++){
        initheap(temp_arr+i);
    }

    //直接选择前k个入堆
    for (int i=0;i<k;i++){
        temp_arr[i].data=interest[i];
        temp_arr[i].index=i;
    }

    /*测试入堆是否成功
    for (int i=0;i<k;i++){
        printf("第%d个数据为%d,他原来的序号是%d\n",i,temp_arr[i].data,temp_arr[i].index);
    }
    */
   
    //建立小顶堆
    for (int i=k/2-1;i>=0;i--){
        heapAdjust(temp_arr,k,i);
    }

    /*测试建立小顶堆是否成功
    for (int i=0;i<k;i++){
        printf("第%d个数据为%d,他原来的序号是%d\n",i,temp_arr[i].data,temp_arr[i].index);
    }
    */

    //对剩下元素进行检查，如果小于堆顶就入堆
    for (int i=k;i<n;i++){
        if(interest[i]<temp_arr[0].data){
            continue;
        }
        initheap(temp_arr);
        temp_arr[0].data=interest[i];
        temp_arr[0].index=i;
        heapAdjust(temp_arr,k,0);
    }

    /*测试入堆是否成功
    for (int i=0;i<k;i++){
        printf("第%d个数据为%d,他原来的序号是%d\n",i,temp_arr[i].data,temp_arr[i].index);
    }
    */
    
    //对临时堆进行排序
    for (int i=k-1;i>0;i--){
        heap temp=temp_arr[0];
        temp_arr[0]=temp_arr[i];
        temp_arr[i]=temp;
        heapAdjust(temp_arr,i,0);//复制粘贴错了，写了heapAdjust(temp_arr,k,0)
    }

    /*测试堆排序是否成功
    for (int i=0;i<k;i++){
        printf("第%d个数据为%d,他原来的序号是%d\n",i,temp_arr[i].data,temp_arr[i].index);
    }
    */

    ///将临时堆中的index赋给top_k_index
    for (int i=0;i<k;i++){
        *(top_k_index+i)=temp_arr[i].index;
    }
    
}
void heapAdjust(heap arr[],int k,int i){
    int maxidx=i;
    int left=2*i+1;
    int right=2*i+2;
    if (left<k&&arr[maxidx].data>arr[left].data){
        maxidx=left;
    }
    if (right<k&&arr[maxidx].data>arr[right].data){
        maxidx=right;
    }
    if (maxidx!=i){
        heap temp=arr[i];
        arr[i]=arr[maxidx];
        arr[maxidx]=temp;
        heapAdjust(arr,k,maxidx);
    }
}//heapAdjust(arr,n,maxidx)传了n进去，导致数组越界，Windows环境运行正常但是Linux暴露问题

void initheap(heap *arr){
    arr->data=0;
    arr->index=0;
}