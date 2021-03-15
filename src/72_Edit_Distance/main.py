
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        size1, size2 = len(word1), len(word2)
        
        # 创建一个(size1+1) * (size2+1)的dp数组，初始化为最大值
        # 这个dp数组的意义是dp[i][j]表示长度为i的word1和长度为j的word2的最小编辑距离
        dp = [[float('inf') for x in range(size2+1)] for y in range(size1+1)]
        
        # 然后初始化base情况
        for row in range(size1+1): dp[row][0] = row # 行代表word1
        for col in range(size2+1): dp[0][col] = col # 列代表word2
            
        # 开始计算，每次基于已有的历史。从上到下，从左到右
        for row in range(1,size1+1):
            for col in range(1,size2+1):
                # 每个位置有三种选择：替换word1，插入到word1，删除word1，选择修改最小的情况
                if word1[row-1] != word2[col-1]:
                    # dp[i][j] = min(dp[i-1][j-1]+1, dp[i][j-1]+1, dp[i-1][j]+1) index别大意啊！！
                    dp[row][col] = min(dp[row-1][col-1]+1, dp[row][col-1]+1, dp[row-1][col]+1)
                else:
                    # dp[i][j] = dp[i-1][j-1]+1 index别大意啊！！
                    dp[row][col] = dp[row-1][col-1]
                    # 因为只加1，所以对角线的替换应该是最少的，否则或是要考虑垂直和水平情况
        
        # 最后的dp[size1][size2]就是所得
        return dp[size1][size2]

if __name__ == "__main__":
  gua = Solution()
  word1, word2 = "horse", "ros"
  rtn = gua.minDistance(word1, word2)
  print("expect result = 3, actual result = %d " % rtn )

  word1, word2 = "intention", "execution"
  rtn = gua.minDistance(word1, word2)
  print("expect result = 5, actual result = %d " % rtn )

