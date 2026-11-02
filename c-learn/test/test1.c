#include<stdio.h>

int maxDiff(int nums[],int a,int b){
    if(a==b){
        return nums[a];
    }else{
    int choose_left=nums[a]-maxDiff(nums,a+1,b);
    int choose_right=nums[b]-maxDiff(nums,a,b-1);
    
    if(choose_left>choose_right){
        return choose_left;
    }
    else return choose_right;
    }
}


int main(){
    int num;
    scanf("%d",&num);
    int arr[num];
    
    //读取数组每个元素
    int i;
    for(i=0;i<num;i++);
    scanf(" %d",&arr[i]);

    if(maxDiff(arr,0,num-1)>=0){
        printf("true\n");
    }else printf("false\n");

    return 0;
}