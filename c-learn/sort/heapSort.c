#include <stdio.h>
#define N 10
void heapAdjust(int arr[],int len,int i);
void heapSort(int arr[],int n);
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

    heapSort(arr,n);

    printf("\n排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void heapAdjust(int arr[],int len,int i){
    int maxidx=i;
    int left=2*i+1;
    int right=2*i+2;
    if (left<len&&arr[left]>arr[maxidx]){
        maxidx=left;
    }
    if (right<len&&arr[right]>arr[maxidx]){
        maxidx=right;
    }
    //原来这里用else if真的不可以，
    //因为如果用了else if就只会分别判断根节点和左右儿子的大小，而不是找到三者之间的最大值
    if (maxidx!=i){
        int temp=arr[i];
        arr[i]=arr[maxidx];
        arr[maxidx]=temp;
        heapAdjust(arr,len,maxidx);//咋又把这玩意放外面了呢，要交换了才去递归
        /*这里为什么要递归呢？
        现在要把以i为根的子树调成大顶堆（爸爸比儿子大）；
        先找这个子树里最大的元素（可能是根i，也可能是左儿子left、右儿子right）；
        如果最大元素不是根（说明根太小了，不符合大顶堆），就把根和最大元素交换 —— 这样当前子树的 “爸爸” 就变成最大的了；
        但交换后，原来的 “小根” 跑到了maxIdx的位置（比如原来的左儿子 / 右儿子位置），这个位置可能有自己的儿子，它可能比自己的儿子还小，破坏了子树的堆结构；
        所以要递归调用adjustHeap，把maxIdx作为新的根，重新调整它的子树，确保这个子树也是大顶堆。
        */
    }
}

void heapSort(int arr[],int n){
    for (int i=n/2-1;i>=0;i--){
        heapAdjust(arr,n,i);
    }
    /*
    这个为什么是n/2-1开始呢
    因为要从最后一个非叶子节点（有儿子的节点）开始
    为什么是n/2-1？结合 “父子关系” 推导：
    已知：爸爸索引i，左儿子索引2*i+1，右儿子索引2*i+2；
    最后一个节点的索引是n-1（因为数组从 0 开始）；
    最后一个节点肯定是某个爸爸的 “左儿子” 或 “右儿子”（完全二叉树的特点）；
    假设最后一个节点是 “左儿子”，则：2*i+1 = n-1 → 解出i=(n-2)/2；
    假设最后一个节点是 “右儿子”，则：2*i+2 = n-1 → 解出i=(n-3)/2；
    不管哪种情况，用整数除法n/2-1都能覆盖这两种情况（比如 n=5 时，5/2-1=2-1=1，和 (n-2)/2=(5-2)/2=1.5→整数 1 一致；n=6 时，6/2-1=3-1=2，和 (n-2)/2=(6-2)/2=2 一致）。
    简单说：这个公式是 “反向利用父子关系”，从最后一个节点倒推它的爸爸，这个爸爸就是 “最后一个非叶子节点”。
    */
    for (int i=n-1;i>0;i--){
        int temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        heapAdjust(arr,i,0);
        /*
        这里还挺有意思的，因为中间数组长度刚好是n-1，而i刚好就是n-1
        而且，为什么要将0传进heapAdjust呢，因为
        核心原因：后续调整时，只有堆顶是 “乱的”，其他子树都已经是大顶堆！
        不用再进行遍历了
        */
    }
}