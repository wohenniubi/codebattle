from typing import List

class Solution:
    #Runtime: 260 ms, faster than 58.44%
    #Memory Usage: 16.8 MB, less than 28.38%
    def subarraySum(self, nums: List[int], k: int) -> int:
        # 思路是prefixsum + 快慢索引
        size = len(nums)
        helper = {0:1} # 存储的全部是以nums[0]作为起始点的subarray, key为subarray sum
        #初始化为0，保证单个元素=k时也可以被找到

        prevSum, rtn = 0, 0
        for i in range(len(nums)):
            prevSum += nums[i]
            remaink = prevSum - k
            if remaink in helper:
                # 说明当前i这个位置的subArray可以与先前的subArray一起构成k值
                rtn += helper[remaink]

            helper[prevSum] = helper.get(prevSum, 0) + 1

        # 下面的操作完全不行
        #preSum = [0]*(size + 1)
        ## 获得前缀和数组是为了转换为单调数组，这样后续就可以greedy计算
        #for i in range(size):
        #    preSum[i+1] = preSum[i]+nums[i]

        # subSum, lhs, i = 0, -1, 0
        # while lhs < i:
        #     subSum = (preSum[i+1]-preSum[lhs+1])
        #     # subSum += nums[i]
        #     # 触发条件
        #     if subSum == k:
        #         rtn+=1
        #     if subSum > k:
        #         # 此时要移除最左边的sum，这里用到preSum，同时更新左边索引
        #         # subSum -= (preSum[lhs+1] - preSum[lhs])
        #         lhs += 1
        #     if i == size-1 and lhs < i: lhs+=1 #避免死循环
        #     if i < size-1: i+=1
        return rtn
    
    # Example1: [1,1,1]
    # preSum = [0, 1, 2, 3], lhs = 0
    # i = 0: subSum = (preSum[1]-preSum[0]) -> 1 -> rtn=0, lhs=-1
    # i = 1: subSum = (preSum[2]-preSum[0]) -> 2 -> rtn=1, lhs=-1
    # i = 2: subSum = (preSum[3]-preSum[0]) -> 3 -> rtnrtn=2, subSum=1, lhs=2
    # return rtn
    
    # Example2: [3,2,1]
    # preSum = [0, 3, 5, 6]
    # i = 0: subSum = 3 -> rtn=1, subSum=0, lhs=1
    # i = 1: subSum = 2
    # i = 2: subSum = 3 -> rtn=2, subSum=1, lhs=2


if __name__ == "__main__":
  gua = Solution()
  rtn = gua.subarraySum([1,-1,0], 0)
  print("expect result = 3, actual result = %d " % rtn )

  rtn = gua.subarraySum([1], 0)
  print("expect result = 0, actual result = %d " % rtn )

  rtn = gua.subarraySum([3,2,1], 3)
  print("expect result = 2, actual result = %d " % rtn )

  rtn = gua.subarraySum([1,1,1], 2)
  print("expect result = 2, actual result = %d " % rtn )

