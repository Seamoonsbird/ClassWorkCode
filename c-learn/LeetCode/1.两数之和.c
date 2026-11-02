/*
 * @lc app=leetcode.cn id=1 lang=c
 *
 * [1] 两数之和
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int result = 0;
    int *resultNums = (int *)malloc (2*sizeof(int));
    for (int i=0;i<numsSize-1;i++){
        for (int j=i+1;j<numsSize;j++){
            result=*(nums+i)+*(nums+j);
            if (result==target){
                *(resultNums)=i;
                *(resultNums+1)=j;
                *returnSize = 2;
                return resultNums;
            }else {
                continue;
            }
        }
    }
    free(resultNums);
    *returnSize=0;
    return resultNums;
}
// @lc code=end

