
from typing import List

class Solution:
    # Runtime: 1124 ms, faster than 65.83%
    # Memory Usage: 28.5 MB, less than 28.83%
    def maxProfit(self, prices: List[int]) -> int:
        #采用了空间压缩, 这样四个dp数组降维成为O(1)
        buy1, sell1, buy2, sell2 = -prices[0], 0, -prices[0], 0
        # buy1, sell1, buy2, sell2 = -prices[0], float('-INF'), -prices[0], -float('-INF')
        size = len(prices)

        for i in range(1, size):
            # 由于要使用昨天的dp值，所以调整一下顺序，倒着计算；别大意啊！！
            sell2 = max(buy2+prices[i], sell2)
            buy2 = max(sell1-prices[i], buy2)
            sell1 = max(buy1+prices[i], sell1)
            buy1 = max(-prices[i], buy1)
        return sell2

    # Runtime: 1540 ms, faster than 19.77%
    # Memory Usage: 29.2 MB, less than 21.17%
    def maxProfit1(self, prices: List[int]) -> int:
        # 采用一般意义的dp搞不定，必须采用状态dp
        size = len(prices)
        dp = [[0 for j in range(size)] for i in range(4)]

        # dp[0][i],dp[1][i],dp[2][i]和dp[3][i]分别代表最后一笔操作是第一次买入，第一次卖出，至多两次买入（不卖出），至多两次卖出的最大收益值
        # 这里小技巧将第一次买入和第二次买入设置为价值的负值，这样就都转化为寻求最大值，不过必须要从0行到3行依次计算；
        # 初始化第一次买入和第二次买入的最值为负数，第一次卖出和第二次卖出的最值为0
        dp[0][0], dp[2][0] = -prices[0], -prices[0]

        for i in range(1,size):
            dp[0][i] = max(dp[0][i-1], -prices[i]) # 第一次买入始终用最小值
            # 大意了，应该用昨天的dp值
            # dp[1][i] = max(dp[1][i-1], prices[i] + dp[0][i])
            # dp[2][i] = max(dp[2][i-1], dp[1][i] - prices[i])
            # dp[3][i] = max(dp[3][i-1], prices[i] + dp[2][i])
            dp[1][i] = max(dp[1][i-1], prices[i] + dp[0][i-1])
            dp[2][i] = max(dp[2][i-1], dp[1][i-1] - prices[i])
            dp[3][i] = max(dp[3][i-1], prices[i] + dp[2][i-1])

        return max(dp[1][size-1], dp[3][size-1])

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.maxProfit(prices=[3,3,5,0,0,3,1,4])
    print("expect result = 6, actual result = %d " % rtn )

    rtn = gua.maxProfit(prices=[7,6,4,3,1])
    print("expect result = 0, actual result = %d " % rtn )

    rtn = gua.maxProfit(prices=[1,2,3,4,5])
    print("expect result = 4, actual result = %d " % rtn )


