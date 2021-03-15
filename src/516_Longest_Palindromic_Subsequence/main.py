
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        # 我觉得思路还是和之前的一道题差不多，从对角线上开始
        
        # 先写成二维数组，一会儿再考虑空间压缩
        size = len(s)
        dp = [[0 for x in range(size)] for x in range(size)]
        
        # 然后初始化对角线上的值，即一个char的情况, 必定是parlindrome
        for i in range(size):
            dp[i][i] = 1
        
        # 现在开始len=2直到len=size的更新
        for subLen in range(2, size+1):
            # i是substr的最左边的起始index，为了保证j-i+1 = subLen且j不越界，即j<=size-1，所以i最大不应该超过size-subLen
            for i in range(size-subLen+1):
                # size-1 - (size-subLen) + 1 = 
                j = i+subLen-1
                
                # 现在开始更新dp[i][j]
                if subLen == 2:
                    dp[i][j] = 2 if s[i] == s[j] else dp[i][i]
                else:
                    # subLen == 3:
                    # dp[i][j] = dp[i+1][j-1] + 2 if s[i] == s[j] else dp[i][j-1] 大意啦
                    dp[i][j] = dp[i+1][j-1] + 2 if s[i] == s[j] else max(dp[i][j-1],dp[i+1][j])
                
        return dp[0][size-1]

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.longestPalindromeSubseq(s = "caab")
  print("expect result = 2, actual result = %d " % rtn )

  rtn = gua.longestPalindromeSubseq(s = "bbbcb")
  print("expect result = 4, actual result = %d " % rtn )

