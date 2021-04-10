
from typing import List

class Solution:

    def maxResult(self, nums: List[int], k: int) -> int:
        # 优化的地方在于，计算dp[i]的时候就是在使用[i-k,i-1]这个dp数组里面的最大值与nums[i]进行相加
        # 那么把nums[i]抛开，岂不就是size=k的滑动窗里面找最大值？那么把外部框架换成最大窗

        n = len(nums)
        dp = [0] * n #因为st只记录pos，所以还需要dp存储历史信息
        dp[0] = nums[0]

        st = [0] # 这样可以保证st始终有值
        for i in range(1,n):
            dp[i] = dp[st[0]] + nums[i]

            while st and dp[st[-1]] < dp[i]:
                # 这里的dp[st[0]]是范围内的最大值，与nums[i]相加得到dp[i]
                # 然后dp[i]会pop数组里面比它小的值
                st.pop(-1)
            # 跳出while循环说明st为空，或者dp[st[-1]]值比dp[i]大，此时把i加入到st
            st.append(i)

            # 要等到i=k-1时才可以持续输出，同时顺便去掉失效的最大值，保证下次计算时dp[st[0]]合法
            # if i >= k-1:
            if i - st[0] >= k:
                st.pop(0)
        return dp[-1]

    def maxResult1(self, nums: List[int], k: int) -> int:
        # 先写出来一个基础版本，然后再改进，复杂度O(k*n)

        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]

        for i in range(1, n):
            dp[i] = float('-inf')
            for j in range(1,k+1): # 共有k种选择，是长度，所以最少为1
                if i >= j:
                    # 因为当前位置会计算很多遍，所以要取max
                    dp[i] = max(dp[i], dp[i-j] + nums[i]) # 跳j长度到i，那么先前的pos与i满足i-pos=j
                else:
                    break

        return dp[-1]

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.maxResult(nums=[1,-1,-2,4,-7,3], k = 2)
    print("expect result = 7, actual result = ", rtn)

    rtn = gua.maxResult(nums=[10,-5,-2,4,0,3], k = 3)
    print("expect result = 17, actual result = ", rtn)

    rtn = gua.maxResult(nums=[1,-5,-20,4,-1,3,-6,-3], k = 2)
    print("expect result = 0, actual result = ", rtn)

