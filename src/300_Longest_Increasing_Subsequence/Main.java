
class Solution {
    //Runtime: 56 ms, faster than 61.32%
    //Memory Usage: 38.8 MB, less than 55.90%
    public int lengthOfLIS(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        
        int rtn = 0;
        int size = nums.length;
        int[] dp = new int[size];
        for (int i = 0; i < size; ++i)
            dp[i] = 1;//初始化：每个subsequence仅含一个数，故长度为1
        
        // 然后本质上是个DFS+memo的操作，这里dp的含义是从左边开头、以当前位置i结束的数组中的最长子序列
        // 从右边的计算会利用左边计算的结果，左边的结果是已经计算出来的最优解，然后最大值在过程中产生
        for (int i = 0; i < size; ++i) {
            for (int j = i-1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
            rtn = Math.max(rtn, dp[i]);
        }
        
        return rtn;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    int rtn;

    int [] nums = {10,9,2,5,3,7,101,18};
    rtn = gua.lengthOfLIS(nums);
    System.out.println("expect value = 4, actual value = " +rtn);
    
    nums = new int[]{0,1,0,3,2,3}; 
    rtn = gua.lengthOfLIS(nums);
    System.out.println("expect value = 4, actual value = " +rtn);
   
    nums = new int[]{1,1,1,1,1,1}; 
    rtn = gua.lengthOfLIS(nums);
    System.out.println("expect value = 1, actual value = " +rtn);
  }
}


