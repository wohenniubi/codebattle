
class Solution:
    # Runtime: 376 ms, faster than 84.02% 
    # Memory Usage: 14.3 MB, less than 94.92%
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        # 来压缩一下空间
        size1, size2 = len(text1), len(text2)
        dp = [0 for j in range(size2+1)]

        for i in range(1, size1+1):
            prev = dp[0] # prev保存的是dp[i-1][j-1]的值，压缩之后变成dp[j-1]
            for j in range(1, size2+1):
                #     a b c d e
                #   0 0 0 0 0 0
                # a 0 0 0 0 0 0
                # c 0 0 0 0 0 0
                # e 0 0 0 0 0 0
                
                # 注意，当保存信息到dp[i][j]时，实际上覆盖了dp[i-1][j]的值，让右侧的计算不正确，
                # 所以要先保留dp[i-1][j]的值，而最早的dp[i-1][j]是0列的值，始终为0
                if text1[i-1] == text2[j-1]:
                    newV = prev + 1 # i被压缩掉了
                else:
                    newV = max(dp[j-1], dp[j]) # 这两部分的值还是不变
                prev = dp[j] # 在即将更新dp[i][j]时，保留当前位置dp[i-1][j]的值，作为下一轮的对角线值
                dp[j] = newV # 此时再更新dp[i][j]的值，dp[i-1][j]已经保留，一切OK
                # if text1[i-1] == text2[j-1]:
                #     dp[j] = dp[j-1] + 1 # i被压缩掉了
                # else:
                #     dp[j] = max(dp[j-1], dp[j])
        return dp[size2]
    
    # Runtime: 428 ms, faster than 56.26%
    # Memory Usage: 23 MB, less than 31.97% 
    def longestCommonSubsequence1(self, text1: str, text2: str) -> int:
        # 两个字符串的操作，dp[i][j]常用于表示text1中i长度的substr和text2中j长度的substr的LCS
        # 先用二维数组，一会儿再压缩空间
        size1, size2 = len(text1), len(text2)
        
        # 行列分别是text1和text2的substr长度，第0行和第0列初始化为0
        dp = [[0 for j in range(size2+1)] for i in range(size1+1)]
        
        # 更新时从左到右，从上到下遍历
        for i in range(1, size1+1):
            for j in range(1, size2+1):
                if text1[i-1] == text2[j-1]:
                    # 出现相同字符的话，直接在上一轮的dp数组基础上+1
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    # 不相同的话就看是去掉text1还是text2
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        
        return dp[size1][size2]

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.longestCommonSubsequence(text1 = "abcba", text2 = "abcbcba")
  print("expect result = 5, actual result = %d " % rtn )

  rtn = gua.longestCommonSubsequence(text1 = "abc", text2 = "abc")
  print("expect result = 3, actual result = %d " % rtn )

  rtn = gua.longestCommonSubsequence(text1 = "abcde", text2 = "ace")
  print("expect result = 3, actual result = %d " % rtn )

  rtn = gua.longestCommonSubsequence(text1 = "abc", text2 = "def")
  print("expect result = 0, actual result = %d " % rtn )

