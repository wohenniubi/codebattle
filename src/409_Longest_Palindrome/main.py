
class Solution:
    # Runtime: 36 ms, faster than 46.18% 
    # Memory Usage: 14.2 MB, less than 61.05%
    def longestPalindrome(self, s: str) -> int:
        # 由于是任意组合字符，因此回文就是偶数个相同的字符
        dict = {}
        
        for c in s:
            dict[c] = dict.get(c,0)+1
        
        rtn, oddCnt = 0, 0
        # for key, cnt in enumerate(dict): 对enumerate的理解有误，它会给item编号；
        # 如果是想类似于C++那样获得key, value对，应该使用items
        # python里面的(key, cnt) = (a, b)等价于key, cnt = (a, b)
        for key, cnt in dict.items():
            isOdd = cnt%2
            oddCnt += isOdd #大意啦，要把全局oddCnt和本地odd区分开
            
            # 偶数的话就全部加入rtn，奇数的话就加入偶数部分
            # rtn += (cnt if not isOdd else (cnt-1))
            rtn += (cnt - isOdd)

        # 对于所有的奇数部分，仅仅只能pick一个
        # rtn += (1 if isOdd else 0) 大意啦，应该用全局oddCnt
        rtn += (1 if oddCnt else 0)
        return rtn

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.longestPalindrome(s = "abccccdd")
  print("expect result = 7, actual result = %d " % rtn )

  rtn = gua.longestPalindrome(s = "a")
  print("expect result = 1, actual result = %d " % rtn )

  rtn = gua.longestPalindrome(s = "bb")
  print("expect result = 2, actual result = %d " % rtn )

  rtn = gua.longestPalindrome(s = "bbc")
  print("expect result = 3, actual result = %d " % rtn )

