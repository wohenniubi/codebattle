
from typing import List

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        # 这道题不能用滑动窗口的原因是存在负数，因此不能简单的看到sum减小就截断认为不包含负数的部分是最大
        # 例如：5,4,-4,7,8，因此要考虑将某个负数sum起来，但同时又要谨防后续的正数不够大的情况

        # 故采用dp，参考最长子序列的dp方法，dp[i]定义为以nums[i]作为子数组最后一个成员的最大sum——相邻是关键
        dp, rtn = nums, nums[0] # 初始化为nunms，每个dp[i]是长度为1的子序列，那就是nums[i]

        for i in range(1,len(nums)): #i=0的情况已经考虑了，所以可以跳过
            # 如果比dp[i]大，才会更新，也就是把前面的子序列纳入考虑，
            dp[i] = max(dp[i], dp[i-1] + nums[i])
            rtn = max(rtn, dp[i])

        # 由于dp的定义，不一定最后一个数是最大，最大可能出现在中间，因此需要遍历；或者过程中就记录rtn
        return rtn# max(dp)

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.maxSubArray(nums = [5, 4, -1, 7, 8])
  print("expect result = 23, actual result = %d " % rtn )

  rtn = gua.maxSubArray(nums = [1])
  print("expect result = 1, actual result = %d " % rtn )

  rtn = gua.maxSubArray(nums = [-2,1,-3,4,-1,2,1,-5,4])
  print("expect result = 6, actual result = %d " % rtn )

