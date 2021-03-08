
import random
from typing import List

class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums #这里仅仅保存nums，不会引入多余的空间

    def pick(self, target: int) -> int:
        # 就是水塘采样的变种
        cnt, i, rtn = 0, 0, -1
        while i < len(self.nums):
            if self.nums[i] == target:
                # 当满足target条件时再开始采样
                cnt += 1
                # if random.random() % cnt < 1: #因为只取一个，所以等价于==0
                # 等价于在[1,cnt]之间取一个随机值
                rand = int(random.random() * cnt)
                if rand % cnt < 1: #因为只取一个，所以等价于==0
                    rtn = i #保存此时的index
            i += 1 # i循环保证while继续执行
        return rtn

if __name__ == "__main__":
  nums = [1,2,3,3,3]
  gua = Solution(nums)
  for i in range(10):
    rtn = gua.pick(target = 3)
    print("%d = %d" % (i+1, rtn))

