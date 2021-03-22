
from typing import List

class Solution:
    # Runtime: 136 ms, faster than 87.27%
    # Memory Usage: 14.3 MB, less than 86.92%
    def change(self, amount: int, coins: List[int]) -> int:
        # 无限背包问题，第i行表示为从0~i的元素，列为amount
        size = len(coins)
        dp = [0 for j in range(amount+1)] # 进行空间压缩
        dp[0] = 1 # 初始化第0列amount=0，coin数凑出amount的combination数为1，空集嘛

        for i in range(1,size+1): # 把coin的面额都遍历一遍
            # 当前在处理coins[0]~coins[i]这些个面额时的组合情况
            coin = coins[i-1] # 注意是找组合数

            # 既然在小于coin时都继承上一级的值，那么稍微改进一点点，直接从coin开始
            for val in range(coin, amount+1):
                dp[val] = dp[val-coin] + dp[val]
        return dp[amount]

    # Runtime: 436 ms, faster than 35.96%
    # Memory Usage: 30 MB, less than 22.79%
    def change1(self, amount: int, coins: List[int]) -> int:
        # 无限背包问题，第i行表示为从0~i的元素，列为amount
        # 还是先2D数组，再进行空间压缩
        size = len(coins)
        dp = [[0 for j in range(amount+1)] for i in range(size+1)]

        # 来进行初始化，第0列amount=0，coin数凑出amount的combination数为1，空集嘛
        for pos in range(size+1):
            dp[pos][0] = 1 # 初始化而已，没毛病

        for i in range(1,size+1): # 把coin的面额都遍历一遍
            # 当前在处理coins[0]~coins[i]这些个面额时的组合情况
            coin = coins[i-1] # 注意是找组合数

            # 既然在小于coin时都继承上一级的值，那么稍微改进一点点，直接从coin开始，不过前提是需要空间压缩
            # for val in range(coin, amount+1):
            #     dp[i][val] = dp[i][val-coin] + dp[i-1][val]
            # 下面代码也是OK的
            for val in range(1,amount+1):
                if val < coin:
                    # 此时肯定是没办法加入coins[i-1]的，继承0到i-1元素的combination集合
                    dp[i][val] = dp[i-1][val]
                else:
                    dp[i][val] = dp[i][val-coin] + dp[i-1][val]

        return dp[size][amount]
        #    0 1 2 3
        # [] 1 0 0 0
        # 2  1 0 1 0

        #    0 1 2 3 4 5
        # [] 1 0 0 0 0 0
        # 1  1 1 1 1 1 1
        # 2  1 1 2 2 3 3
        # 5  1 1 2 3 3 4

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.change(amount = 5, coins = [1,2,5])
    print("expect result = 4, actual result = %d " % rtn )

    rtn = gua.change(amount = 10, coins = [10])
    print("expect result = 1, actual result = %d " % rtn )

    rtn = gua.change(amount = 3, coins = [2])
    print("expect result = 0, actual result = %d " % rtn )

