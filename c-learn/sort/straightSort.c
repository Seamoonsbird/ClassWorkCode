#include <stdio.h>
#define N 100
void straight(int arr[],int n);

int main(void){
    int i=0,j=0;
    int arr[10];

    printf("请问有几个整数：\n");
    int n=0;
    scanf("%d",&n);
    printf("请输入%d个整数：\n",n);
    for (i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("\n");

    straight(arr,n);
    
    printf("排序后的结果为：\n");
    for (i=0;i<n;i++){
        printf("\t%d",*(arr+i));
    }
    printf("\n");
    return 0;
}
void straight(int arr[],int n){
    for (int i=1;i<n;i++){
        int k=-1;
        for (int j=i-1;j>=0;j--){
            if (arr[i]>=arr[j]){
                k=j;
                break;
            }
        }
/*这一点最后想到的，因为如果有一个数比前面任何一个数都要小的话，
那么k就会是0，就相当于说arr[0]第一个数据比他小再进行操作，显然是不合理的
那我就可以将k初始化为-1（此版本加入）*/
        if(k+1==i){
            continue;
        }
        else{
            int temp=arr[i];
            for (int m=i;m>k+1;m--){
                arr[m]=arr[m-1];
            }
            arr[k+1]=temp;
            /*
            这一块的覆盖要注意起与终范围*/
        }
    }
}