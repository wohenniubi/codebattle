from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # 无限次数的股票买卖，那就是任何涨幅都加在一起
        minVal = prices[0]

        rtn = 0 # 又有点像滑动窗口
        for i in range(1, len(prices)):
            if prices[i] > minVal:
                rtn += (prices[i] - minVal)
                minVal = prices[i]
            else:
                minVal = prices[i]

        return rtn

if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.maxProfit(prices=[7,1,5,3,6,4])
    print("expect result = 7, actual result = %d " % rtn )

    rtn = gua.maxProfit(prices=[7,6,4,3,1])
    print("expect result = 0, actual result = %d " % rtn )

    rtn = gua.maxProfit(prices=[1,2,3,4,5])
    print("expect result = 4, actual result = %d " % rtn )

