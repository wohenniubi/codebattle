
from typing import List

class Solution:
    #Runtime: 2200 ms, faster than 9.09%
    #Memory Usage: 30.5 MB, less than 17.25%
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        # 这道的基本思路是单调栈
        memo, rtn = [], []
        size = len(nums)

        for i in range(size):
            # 先加入memo，加入时注意pop较小值；然后在达到滑动窗口上限时再弹出，弹出时进行相应操作

            while memo and nums[memo[-1]] < nums[i]:
                # 当然要rtn有效时才加入，相等时就不pop了
                memo.pop(-1)
            # 跳出while说明memo为空，或者前面一个数>=当前的数
            memo.append(i)

            # 以i作为标志，控制加入rtn
            if i >= k-1:
                rtn.append(nums[memo[0]])

            # 这里负责维护滑动窗的宽度限制
            if i - memo[0] + 1 == k:
                memo.pop(0) # 这次就pop吧，要不然memo里面还会剩下一个，得到for loop外面去处理

        return rtn

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.maxSlidingWindow(nums=[1,3,-1,-3,5,3,6,7],k=3)
  print("expect value = [3,3,5,5,6,7], actual value = ", rtn)

  rtn = gua.maxSlidingWindow(nums=[1],k=1)
  print("expect value = [1], actual value = ", rtn)

  rtn = gua.maxSlidingWindow(nums=[1,-1],k=1)
  print("expect value = [1,-1], actual value = ", rtn)

  rtn = gua.maxSlidingWindow(nums=[9,11],k=2)
  print("expect value = [11], actual value = ", rtn)

