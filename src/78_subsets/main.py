from typing import List

class Solution:
    #Runtime: 36 ms, faster than 58.47%
    #Memory Usage: 14.5 MB, less than 22.68%
    def subsets(self, nums: List[int]) -> List[List[int]]:
        self.rtn = []
        
        # 采用决策树遍历的思路，来呀战个痛快
        def traverse(nums: List[int], pos: int, path: List[int]) ->None:
            if pos == len(nums):
                # self.rtn.append(path) 又大意啦大意了！！！python是reference
                self.rtn.append([x for x in path])
                return
            
            # 现在开始决策，选和不选，是个问题
            for i in range(2):
                # push操作
                if i == 0:
                    path.append(nums[pos])
                
                traverse(nums, pos+1, path)
                
                # pop操作
                if i == 0:
                    path.pop(-1)
            return
        
        path = []
        traverse(nums, 0, path)
        return self.rtn

if __name__ == "__main__":
  gua = Solution()
  # nums = [1,2,3]
  # rtn = gua.permute(nums)
  # print(rtn)
  rtn = gua.subsets([1,2,3])
  print(rtn)

