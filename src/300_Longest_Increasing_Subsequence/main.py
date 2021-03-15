from typing import List

class Solution:
    # Runtime: 96 ms, faster than 75.75%
    # Memory Usage: 14.8 MB, less than 5.96%
    def lengthOfLIS(self, nums: List[int]) -> int:
        lenByNow = []
        for i in range(len(nums)):
            # 二分查找复习一下，找到递增序列lenByNow中，小于且最接近num的那个值的index
            num = nums[i]
            lhs, rhs = 0, len(lenByNow)
            while lhs < rhs:
                # mid = lhs + (rhs-lhs) 怎么大意成这样！！！
                mid = lhs + int((rhs-lhs)/2)
                if lenByNow[mid] == num:
                    rhs = mid
                elif lenByNow[mid] > num:
                    rhs = mid
                else:
                    lhs = mid+1
            
            # lhs是需要的index
            if lhs == len(lenByNow):
                lenByNow.append(num)
            else:
                lenByNow[lhs] = num
        # 因为不需要返回具体的序列，所以直接是len(lenByNow)就OK了
        return len(lenByNow)

    # Runtime: 3928 ms, faster than 34.53%
    # Memory Usage: 14.4 MB, less than 92.51% 
    def lengthOfLIS(self, nums: List[int]) -> int:
        # 这里dp的定义很巧妙，dp[i]保存以nums[i]为结尾的subsequence的最长值，这样才能具有子问题属性
        size = len(nums)
        lenByNow = [1 for _ in range(size)]
        
        for i in range(1,size):
            # 然后内部从i-1到0
            for j in range(i-1,-1,-1):
                if nums[i] > nums[j]: # 题目要求是strick严格大于
                    # lenByNow[i] = lenByNow[j]+1
                    # break #这里greedy了一下，肯定越靠近i的越长
                    # ——不对！不能break要继续努力，前面可能还有更好的
                    lenByNow[i] = max(lenByNow[i], lenByNow[j]+1)

        # 由于dp不是最终的目的，而是中间过程，最后还要遍历一遍dp，找到里面的最值
        rtn = max(lenByNow)
        return rtn
        
if __name__ == "__main__":
  gua = Solution()
  rtn = gua.lengthOfLIS(nums = [10,9,2,5,3,7,101,18])
  print("expect result = 4, actual result = %d " % rtn )

  rtn = gua.lengthOfLIS(nums = [0,1,0,3,2,3])
  print("expect result = 4, actual result = %d " % rtn )

  rtn = gua.lengthOfLIS(nums = [3,3,3,3,3,3])
  print("expect result = 1, actual result = %d " % rtn )


