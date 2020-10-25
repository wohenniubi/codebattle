# coding=utf-8

class Solution(object):
    #Runtime: 20 ms, faster than 69.13% 
    #Memory Usage: 13.4 MB, less than 6.26%
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        size = len(nums)
        if size == 0:
            return 0
        elif size == 1:
            return nums[0]
        p2, p1 = 0, nums[0]

        # 状态方程 dp[i] = max(dp[i-1], dp[i-2]+nums[i])
        for i in range(1, size):
            p2, p1 = p1, p2
            p1 = max(p2, (nums[i] + p1))

        return p1

if __name__ == "__main__":
  gua = Solution()
  nums = [1,2,3,1]
  rtn = gua.rob(nums)
  print("expect value = 4, actual value = %d" % (rtn))

