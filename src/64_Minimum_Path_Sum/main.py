
from typing import List

class Solution:
    def minPathSum1(self, grid: List[List[int]]) -> int:
        # 就是二维的DP吧，矩阵本身就是个dp数组
        m, n = len(grid), len(grid[0])
        dp = [[0 for j in range(n)] for i in range(m)]
        
        # 初始化一下第0行，第0列
        dp[0][0] = grid[0][0]
        for i in range(1,m):
            # dp[i][0] += dp[i-1][0] 大意了啊！！
            dp[i][0] = dp[i-1][0] + grid[i][0]
        
        for j in range(1,n):
            # dp[0][j] += dp[0][j-1] 大意了啊！
            dp[0][j] = dp[0][j-1] + grid[0][j]
        
        for i in range(1,m):
            for j in range(1,n):
                # 有两个来源，水平和垂直
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        
        return dp[m-1][n-1]
    
    # Runtime: 88 ms, faster than 97.47%
    # Memory Usage: 15 MB, less than 92.40%
    def minPathSum(self, grid: List[List[int]]) -> int:
        # 压缩空间试一试
        m, n = len(grid), len(grid[0])
        dp = grid[0]
        for j in range(1,n):
            dp[j] += dp[j-1]
            
        for i in range(1,m):
            dp[0] += grid[i][0]
            # prev = dp[0]
            for j in range(1,n):
                # 因为不用保存左斜上方的值，所以不用保存旧值，直接存储在dp[i]里面
                #dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
                # tmp = min(dp[j], prev) + grid[i][j]
                # prev = dp[j]
                # dp[j] = tmp
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j]

        return dp[-1]


if __name__ == "__main__":
    gua = Solution()
    rtn = gua.minPathSum(grid = [[1,3,1],[1,5,1],[4,2,1]])
    print("expect result = 7, actual result = %d " % rtn )

    rtn = gua.minPathSum(grid = [[1,2,3],[4,5,6]])
    print("expect result = 12, actual result = %d " % rtn )



