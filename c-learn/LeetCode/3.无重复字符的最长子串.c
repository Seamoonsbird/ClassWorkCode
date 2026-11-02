/*
 * @lc app=leetcode.cn id=3 lang=c
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
int lengthOfLongestSubstring(char* s) {
    int max=0;
    int length = strlen(s);
    for (int i=0;i<length;i++){
        int count=0;
        int record[128]={0};
        for (int j=i;j<length;j++){
            char c = s[j];
            if (record[c]==0){
                record[c]=1;
                count++;
                if(count>max){
                    max=count;
                }
            }else{
                break;
            }
        }
    }
    return max;
}
// @lc code=end

