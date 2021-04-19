
class Solution:
    # Runtime: 940 ms, faster than 81.08% 
    # Memory Usage: 14.3 MB, less than 62.15%
    def longestPalindrome(self, s: str) -> str:
        # 找到以s[i]和s[j]为中心的最长回文
        def getParlindrom(s: str, i: int, j: int)->str:
            rtn = ""
            while i>=0 and j < len(s) and s[i] == s[j]:
                # rtn = s[i:j] 大意了，这是取[i,j)之间的substr
                # rtn = s[i:j+1] # 稍微改进一下，这里不需要给rtn赋值，最后才赋值
                i -= 1
                j += 1
            # 跳出while时，rtn必定是最长的
            
            rtn = s[i+1:j] # 把i和j各自向中间回退一步时的rtn是最长的
            return rtn
        
        # 霸气外漏直接greedy查找，效率或超过dp哟，空间复杂度也只有O(n)
        size = len(s)
        if size <= 1:
            return s # 这种情况默认就是回文
        
        # 本来i是在[0,size)之间，但是由于需要处理size-2和size-1为中心的情况，所以i不能超过size-1
        rtn = ""
        for i in range(size-1): 
            str1 = getParlindrom(s, i, i)   # 以s[i]为中心，向两侧扩展
            str2 = getParlindrom(s, i, i+1) # 以s[i]和s[j]为中心，向两侧扩展
            
            if len(rtn) < len(str1):
                rtn = str1
            if len(rtn) < len(str2):
                rtn = str2
        
        return  rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.longestPalindrome(s="babad")
    print("expect result = bab, actual result = ", rtn)

    rtn = gua.longestPalindrome(s="cbbd")
    print("expect result = bb, actual result = ", rtn)

    rtn = gua.longestPalindrome(s="a")
    print("expect result = a, actual result = ", rtn)

    rtn = gua.longestPalindrome(s="ac")
    print("expect result = a, actual result = ", rtn)

