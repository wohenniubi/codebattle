
from typing import List

class Solution:
    #Runtime: 32 ms, faster than 78.33%
    #Memory Usage: 14.1 MB, less than 92.47%
    def removeElement(self, nums: List[int], val: int) -> int:
        '''
        居然说“It doesn't matter what you leave beyond the new length.”
        这么随意的吗。。。 好吧不吐槽了，还是快慢索引解决
        '''
        size = len(nums)
        if not size : return 0
        
        #lhs, cnt = 0, 0 
        # 由于nums可能全部都是val，那么所有的数据都会被删除，故不能用lhs作为最终的长度，得专门用一个cnt ——不对
        lhs = 0 
        # 好像就用lhs就可以了，因为lhs总是指向一个即将被存入数据的pos，pos-1就是最后一个存入了数据的位置
        # 而由位置转换为长度需要+1，也就是pos + 1 即lhs，所以直接返回lhs就好了
        for i in range(size):
            if nums[i] == val:
                # i这个位置要被删除，那么也不用保存到lhs里面了
                pass # lhs也保持不变
            else:
                # 不是val的话，当前位置的nums[i]存一下，然后lhs移位
                nums[lhs] = nums[i]
                # cnt += 1
                lhs += 1 
        
        # 为了方便外部打印，我还是去掉了后面的多余数据
        for i in range(lhs, size):
          nums.pop(-1)

        return lhs

if __name__ == "__main__":
  gua = Solution()

  nums = [3,2,1,6,0,5]
  print(nums)
  rtn = gua.removeElement(nums, 2)
  print(f"expect result = 5, actual result = {rtn}")
  print(nums)

  nums = [3,2,2,3]
  print(nums)
  rtn = gua.removeElement(nums, 3)
  print(f"expect result = 2, actual result = {rtn}")
  print(nums)

