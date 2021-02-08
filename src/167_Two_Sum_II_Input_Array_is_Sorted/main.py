from typing import List

class Solution:
    #Runtime: 64 ms, faster than 67.50%
    #Memory Usage: 14.4 MB, less than 99.72%
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        # 由于确保是递增的数组，那么解决办法就是滑动窗，左右索引向中间塌缩
        lhs, rhs = 1, len(numbers) # 这里是1-indexed，所以相当于[0,len-1]区间
        
        while lhs <= rhs:
            sum2 = numbers[lhs-1] + numbers[rhs-1]
            if sum2 == target:
                return [lhs, rhs]
            elif sum2 < target:
                lhs += 1    #说明左边小了
            else:
                rhs -= 1    #说明右边大了
        
        return [0,0] # 万一while循环找不到数据，那么返回1-index下的异常值
   

if __name__ == "__main__":
  gua = Solution()

  nums, target = [2,7,11,15], 9
  print(nums, end="")
  print("  target = %d" % target)
  rtn = gua.twoSum(nums, target)
  print(f"expect result = [1,2], actual result = [{rtn[0]},{rtn[1]}]")


