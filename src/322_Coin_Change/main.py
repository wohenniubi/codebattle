
from typing import List

class Solution:
    # Runtime: 1292 ms, faster than 60.64%
    # Memory Usage: 14.6 MB, less than 53.97%
    def coinChange(self, coins: List[int], amount: int) -> int:
        # 如果硬要用无限背包问题的思路，即：以coins面额作为外部循环，内循环是amount
        # 那么一定要进行空间压缩，dp的定义很重要，仅包含coins[0] ~ coins[i]面额时的最小值
        # 否则还需要一个for loop来提取不同面额下的最小个数
        minCnt = [-1 for x in range(amount+1)] # float('INF')
        minCnt[0] = 0
        for coin in coins:
            for i in range(coin, amount+1):
                if i == coin:
                    minCnt[i] = 1 # 此时一个coin就搞定
                else:
                    # 此时要考虑是否能够从dp[i - coin]一步到位，以及是否dp[i]已经存在
                    if minCnt[i] != -1:
                        minCnt[i] = min(minCnt[i], \
                            minCnt[i-coin] + 1 if minCnt[i-coin] != -1 else amount+1)
                    else:
                        minCnt[i] = minCnt[i-coin] + 1 if minCnt[i-coin] != -1 else -1
        return minCnt[amount]

if __name__ == "__main__":
  gua = Solution()
  coins, amount = [], -1
  rtn = gua.coinChange(coins = [1,2,5], amount = 11)
  print("expect result = 3, actual result = %d " % rtn )

  rtn = gua.coinChange(coins = [2,5,10,1], amount = 27)
  print("expect result = 4, actual result = %d " % rtn )

  rtn = gua.coinChange(coins = [2], amount = 3)
  print("expect result = -1, actual result = %d " % rtn )

  rtn = gua.coinChange(coins = [1], amount = 0)
  print("expect result = 0, actual result = %d " % rtn )

  rtn = gua.coinChange(coins = [1], amount = 1)
  print("expect result = 1, actual result = %d " % rtn )

  rtn = gua.coinChange(coins = [1], amount = 2)
  print("expect result = 2, actual result = %d " % rtn )

