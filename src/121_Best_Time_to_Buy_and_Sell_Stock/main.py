
from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # 本题的思路其实用到了dp，最值找到目前为止的最小值，这样用当前值与最小值相减就可以得到最大的差距
        # 然后同时进行了空间压缩，因此才可以在O(1)空间复杂度搞定

        # 其中dp[0][*]表示目前位置的最小值，dp[1][*]表示目前的最大差值
        size = len(prices)
        dp = [[0 for j in range(size)] for i in range(2)]
        dp[0][0] = prices[0]

        for i in range(1,size):
            dp[0][i] = min(dp[0][i-1], prices[i])
            dp[1][i] = max(dp[1][i], prices[i] - dp[0][i])

        # return dp[1][size-1]
        return max(dp[1]) # 最大值在其中

if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.maxProfit(prices=[7,1,5,3,6,4])
    print("expect result = 5, actual result = %d " % rtn )

    rtn = gua.maxProfit(prices=[7,6,4,3,1])
    print("expect result = 0, actual result = %d " % rtn )

