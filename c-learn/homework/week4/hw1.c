#include <stdio.h>
void swap(int array[],int i,int j);

int main()
{
    int arr[6] = {9, 3, 7, 1, 6, 2};
int n = 6;
for (int i=0;i<n;i++){
        int flag=1;
        for (int j=0;j<n-i-1;j++){
            if (arr[j]>arr[j+1]){
                swap(arr,j,j+1);
                flag=0;
            }
        }
        if (flag){
            break;
        }
    }

    printf("排序后的结果为：\n");
    for (int i=0;i<n;i++){
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
