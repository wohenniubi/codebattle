
class Solution:
    #Runtime: 784 ms, faster than 57.48%
    #Memory Usage: 18.7 MB, less than 55.92%
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        # 估计还是采用dp，二维dp，以删除字符的模版
        len1, len2 = len(s1), len(s2)
        
        # 多一行多一列便于让for循环方便处理，这里dp[i][j]表示让s1.substr(0,i)和s2.substr(0,j)相同时删除的ASCII码的最小sum
        dp = [[0 for col in range(len2+1)] for row in range(len1+1)]
        
        # 初始化第0行和第0列
        for col in range(1,len2+1): # 别大意写错啦range(len2+1)
            dp[0][col] = dp[0][col-1] + ord(s2[col-1]) # 第0行s1是空的，因此删除s2中的所有字符
        
        for row in range(1,len1+1): # 别大意写错啦range(len1+1)
            dp[row][0] = dp[row-1][0] + ord(s1[row-1]) # 第0列s2是空的，因此删除s1中的所有字符
            
        for row in range(1,len1+1):
            for col in range(1, len2+1):
                if s1[row-1] == s2[col-1]:
                    # 相同的时候就不用删啦，开心
                    dp[row][col] = dp[row-1][col-1] 
                else:
                    # 出现不相同的情况了，要从s1或者s2中删除一个字符
                    dp[row][col] = min(dp[row-1][col]+ord(s1[row-1]), dp[row][col-1] + ord(s2[col-1]))
        
        return dp[len1][len2]

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.minimumDeleteSum(s1 = "delete", s2= "leet")
  print("expect result = 403, actual result = %d " % rtn )

  rtn = gua.minimumDeleteSum(s1 = "sea", s2 = "eat")
  print("expect result = 231, actual result = %d " % rtn )

