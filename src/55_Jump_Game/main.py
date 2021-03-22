
from typing import List

class Solution:
    # Runtime: 92 ms, faster than 46.43% 
    # Memory Usage: 16 MB, less than 83.20%
    def canJump(self, nums: List[int]) -> bool:
        # 看似dp问题，实际上可以用greedy
        # 0   1 2  3  4
        # 2---->|
        #     3------>|
        #       1->|
        #          1->|
        #             4
        size = len(nums)
        maxJump = 0 # greedy计算当前能过到达的最远index
        # for i in range(size): 解决不了nums=[0]这个坑 
        for i in range(size-1): # 多么机智的处理，去掉最后一个元素之后判断最远index
            maxJump = max(maxJump, i + nums[i])
            if maxJump <= i:
                # 说明没有进步，或者说卡在原地了，不能更新整体最远index
                return False
        return maxJump+1 >= size

    # 时间复杂度O(len(nums)*10^4)，超时
    def canJump1(self, nums: List[int]) -> bool:
        dp = [0 for i in range(size)]
        dp[-1] = True #初始化一下最后的到达状态
        
        # 从后（右）往前（左）遍历每个位置的元素
        for i in range(size-1, -1, -1):
            # 先从当前能cover的最远位置开始算起，一旦远端位置是True，那么就可以到达最后
            for j in range(nums[i], -1, -1): #因为是非负整数，所以nums[i]可以为0哟
                if i + j < size and dp[i+j]: 
                    dp[i] = True
                    break # 当前位置可以到达，然后就greedy的选择这个位置来跳
        return dp[0]

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.canJump(nums=[2,3,1,1,4])
  print("expect result = 1, actual result = %d " % rtn )

  rtn = gua.canJump(nums=[3,2,1,0,4])
  print("expect result = 0, actual result = %d " % rtn )

