from typing import List

class Solution:
    #Runtime: 3844 ms, faster than 5.39%
    #Memory Usage: 15.7 MB, less than 39.23%
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        '''
        这道题有难度，第二次又忘记了。。
        基本思路是在平均数的上下限中间进行二分查找，看是否存在长度为k的字段
        中间的mid函数用于判断是否存在k长度的字段，很巧妙
        '''

        # 这个函数用于检查数据中是否存在一个长度至少为k的子数组，其平均数要大于maxAvg
        # 或者说，是否存在一个长度至少为k的子数组，它的sum - maxAvg*len(子数组) > 0
        def subArrayExist(nums: List[int], maxAvg: float, k: int) -> bool:
            # 这里非常巧妙，为了判断是否存在长度为k的子数组，greedy来找一个以0为起点、长度至多为i-k的最小sum的子数组
            # 然后再用[0,i)的子数组减去最小sum的子数组，得到一个长度至少为k的子数组sum，
            prevSum = [x for x in nums]
            prevSum.insert(0, 0) # 创建一个前缀和数组

            minSum = 0 # 这个是nums里面以0为起点的最小子数组
            # 这里在循环时最好从1开始，这样意义更好理解
            # for i in range(len(nums)):
            for i in range(1, len(nums)+1):
                # 在数据中直接减去maxAvg，这样不需要再除以N了；prevSum存的是[0,i]这个范围内的所有数与maxAvg的差
                # prevSum[i+1] = prevSum[i] + nums[i] - maxAvg
                prevSum[i] = prevSum[i-1] + nums[i-1] - maxAvg

                # 这里有点像滑动窗的操作，当可以凑出窗长时，计算以0为起点的子数组的最小值
                # 注意一下边界pevSum[i]是[0,i]的子数组和，因此prevSum[i-k]是[0,i-k-1]的子数组和
                # if i > k: 在i>=k时就可以了，此时prevSum[0]正好为0，且此时的prev[i+1]正好不需要
                if i >= k:
                    minSum = min(minSum, prevSum[i-k])

                # 两者相减得到的至少是[i-k, i]的子数组
                # if i > k and prevSum[i+1] - minSum > 0:
                # if i >= k and prevSum[i+1] - minSum > 0:
                if i >= k and prevSum[i] - minSum > 0:
                    return True
            return False


        lhs , rhs = min(nums), max(nums)

        while lhs + 1e-5 < rhs:
            mid = lhs + (rhs - lhs)/2
            isExist = subArrayExist(nums, mid, k)
            if isExist:
                # 说明mid可能给小了，所以才会出现大于0的情况，那么让lhs变大
                lhs = mid
            else:
                # 说明mid可能给大了，所以没有找到大于0的情况，那么让rhs变小
                rhs = mid

        return lhs

if __name__ == "__main__":
  gua = Solution()
  nums, k = [1,12,-5,-6,50,3], 4
  rtn = gua.findMaxAverage(nums, k)
  print(f"expect result = 12.75, actual result = {rtn}")

  nums, k = [5], 1
  rtn = gua.findMaxAverage(nums, k)
  print(f"expect result = 5.0, actual result = {rtn}")


