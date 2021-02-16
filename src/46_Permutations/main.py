
from typing import List

rst = []

class Solution:
    #Runtime: 44 ms, faster than 42.31%
    #Memory Usage: 14.6 MB, less than 17.15%
    def permute(self, nums: List[int]) -> List[List[int]]:
        if len(nums) < 2: return [nums]
        
        # 就是决策树的遍历，首选递归操作; 由于是产生所有的排列，估计不需要memo了
        path, pos = [], 0 # 用来保存path和记录当前到决策树的哪一层了
        
        # 这种做法非常讨巧，把path和nums合并到一起了
        # def traverse(nums: List[int], pos: int, path: List[int]):
        def traverse(nums: List[int], pos: int):
            global rst
            if pos == len(nums):
                # rst.append(nums)
                rst.append([x for x in nums])
                return
            
            for i in range(pos, len(nums)):
                nums[i], nums[pos] = nums[pos], nums[i]
                traverse(nums, pos+1)
                nums[i], nums[pos] = nums[pos], nums[i]
        
        traverse(nums, pos)
        return rst

if __name__ == "__main__":
  gua = Solution()
  nums = [1,2,3]
  rtn = gua.permute(nums)
  print(rtn)



