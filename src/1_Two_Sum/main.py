from typing import List

class Solution:
    # Runtime: 44 ms, faster than 84.63%
    # Memory Usage: 14.4 MB, less than 75.13%
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # rtn = []
        helper = {}
        # 要求index不变，那就使用查找的方法
        for index in range(len(nums)):
            remain = target - nums[index]
            if remain in helper:
                return [helper[remain], index]
            else:
                helper[nums[index]] = index

        # 因为说了必定有解，所以这里只是写一下而已
        return [-1, -1]

if __name__ == "__main__":
  gua = Solution()
  nums = [2,7,11,15]
  rtn = gua.twoSum(nums, 9)
  exp = [0,1]
  print("expect result = ", end=""), print(exp)
  print("actual result = ", end=""), print(rtn)

  nums = [3,2,4]
  rtn = gua.twoSum(nums, 6)
  exp = [1,2]
  print("expect result = ", end=""), print(exp)
  print("actual result = ", end=""), print(rtn)

  nums = [3,3]
  rtn = gua.twoSum(nums, 6)
  exp = [0,1]
  print("expect result = ", end=""), print(exp)
  print("actual result = ", end=""), print(rtn)

