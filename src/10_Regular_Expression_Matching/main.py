
class Solution:
    # Runtime: 40 ms, faster than 90.48% 
    # Memory Usage: 14.7 MB, less than 11.60%
    def isMatch(self, s: str, p: str) -> bool:
        # 这次采用递归做法，可以简化很多操作；可以知道只需要2个状态
        memo = {}
        def dp(posS: int, posP: int) -> bool:
            # 返回条件，非常巧妙的考虑posP而不是posS
            if posP == len(p):
                return posS == len(s)
            
            if (posS, posP) in memo:
                # 判断是否有必要使用memo的前提是存在重复子问题，方法就是看从f(n)到达f(n-2)状态过程中是否出现重复调用
                return memo[(posS, posP)]
            
            # 现在开始处理。首先判断第一个char是否相同，判断的时候要对index进行保护
            first_match = posS < len(s) and p[posP] in [s[posS], '.']
            
            rtn = False
            if posP+1 < len(p) and p[posP+1] == '*':
                # 对于p中下一个char是*的情况，可能是：s="", p=a*; s=a, p=a*; s=aa, p=a*; 前者去掉p两个char，后者去掉s一个char
                rtn = dp(posS, posP+2) or (first_match and dp(posS+1, posP))
            else:
                # 对于p中下一个char不是*的情况，那就各自去掉s和p中的一个char，使用first_match可以巧妙的保护了s的index
                rtn = first_match and dp(posS+1, posP+1)
            memo[(posS, posP)] = rtn
            return rtn
        
        return dp(0,0)

    #Runtime: 48 ms, faster than 73.65%
    #Memory Usage: 14.4 MB, less than 34.72%
    def isMatch1(self, s: str, p: str) -> bool:
        # 如果想不到解决办法，先从简化的问题开始，比如：
        # (1)没有.和* (2)仅有. (3)有.和*
        # 对于(1)和(2)，基本上都是直接先保证长度一致，然后逐个字符比较
        # 加上了*之后, (3)貌似就只能用dp了。dp状态包括s的char，p的char，
        # 还有p中的char如果是*，还需要上一个char的，这都可以归结为当前char
        # 在s和p中的index，二维dp刚好满足这两个条件；选择很简答呀，把s[i]与p[j]进行比较
        
        #    '' c * a * b
        # '' 1  0 1 0 1 0
        # a  0  0 0 1 1 0
        # a  0  0 0 0 1 0
        # b  0  0 0 0 0 1
        
        #    '' . *   dp[i-1][j-2] or dp[i][j-1]
        # '' 1  0 1
        # a  0  1 1
        # b  0  0 1
        # b  0  0 1
        # b  0  0 1
        
        #    '' a b *
        # '' 1  0 0 0
        # a  0  1 0 1
        # b  0  0 1 1
        # b  0  0 0 1
        # b  0  0 0 1
        sizeS, sizeP = len(s), len(p)
        dp = [[0 for j in range(sizeP+1)] for i in range(sizeS+1)]
        
        # 然后初始化dp，第0行和第0列
        dp[0][0] = 1 # 第0列就是这样
        
        # 第0行的处理
        # for j in range(1,sizeP): 又大意了啊！！！
        for j in range(1,sizeP+1):
            if p[j-1] == '*': # 等于'.'或者字母都会false:
                # 题目说了，不会出现*前面没有char的情况，所以dp[j-2]是安全的，否则正则表达式invalid
                dp[0][j] = dp[0][j-2] or dp[0][j-1] # dp[j-2]是去掉前一个char和当前*，dp[j-1]表示去掉当前*
            # else:
            #     dp[j] = False
        
        # 来开始遍历
        # for i in range(1,sizeS): # 大意啦大意啦！！！
        for i in range(1,sizeS+1): 
            # for j in range(1,sizeP): # 太大意了！！！
            for j in range(1,sizeP+1):
                if p[j-1] == '.':
                    # s肯定不包含这个','，所以直接去掉s和p两者的最后一个char
                    dp[i][j] = dp[i-1][j-1]
                elif p[j-1] == '*':
                    # if p[j-2] in ['.' '*']: # == '.': # 大意啊，['.' '*']等于['.*']哦！！
                    if p[j-2] in ['.','*']: # == '.':
                        dp[i][j] = any([dp[i][j-1], dp[i][j-2], dp[i-1][j-1], dp[i-1][j], dp[i-1][j-2]])
                        # dp[i][j] = dp[i][j-1] or dp[i][j-2] or dp[i-1][j-1] or dp[i-1][j] or dp[i-1][j-2]
                    # elif p[j-2] == '*': # 会不会出现**
                    #     pass
                    else:
                        # dp[i][j] = dp[i][j-1] or dp[i][j-2] or dp[i-1][j-1] or dp[i-1][j]
                        if s[i-1] == p[j-2]:
                            dp[i][j] = dp[i][j-1] or dp[i][j-2] or dp[i-1][j-1] or dp[i-1][j]
                        else:
                            dp[i][j] = dp[i][j-2] # 去掉p[j-2]和p[j-1]
                        # dp[i][j] = s[i-1] == p[j-2] and (dp[i][j-1] or dp[i][j-2] or dp[i-1][j-1] or dp[i-1][j]) 
                    # dp[i][j] = dp[i][j-1] or dp[]
                else:
                    # dp[i][j] = s[i-1] == p[j-1] # 错过了一个条件
                    dp[i][j] = s[i-1] == p[j-1] and dp[i-1][j-1]
        
        return dp[sizeS][sizeP]

if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.isMatch(s = "a", p = "ab*")
    print("expect result = 1, actual result = %d " % rtn )

    rtn = gua.isMatch(s = "ab", p = ".*")
    print("expect result = 1, actual result = %d " % rtn )

    # rtn = gua.isMatch(s = "sippi", p = "s*p*.")
    # rtn = gua.isMatch(s = "mississippi", p = "mis*is*p*.")
    rtn = gua.isMatch(s = "si", p = "s*")
    print("expect result = 0, actual result = %d " % rtn )

    rtn = gua.isMatch(s = "", p = ".*")
    print("expect result = 1, actual result = %d " % rtn )

    rtn = gua.isMatch(s = "aa", p = "a")
    print("expect result = 0, actual result = %d " % rtn )

    rtn = gua.isMatch(s = "aa", p = "a*")
    print("expect result = 1, actual result = %d " % rtn )

    rtn = gua.isMatch(s = "aab", p = "c*a*b")
    print("expect result = 1, actual result = %d " % rtn )

