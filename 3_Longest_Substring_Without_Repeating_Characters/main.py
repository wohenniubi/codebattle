
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        # 和76题最小substring有点像，窗长不确定时就先往里面加，然后再缩短
        if len(s) < 2: return len(s)
        
        mapS = {}
        
        lhs = 0; rtn = 1
        for i in range(len(s)):
            x = s[i]
            mapS[x] = 1 if x not in mapS else mapS[x]+1
            
            # 现在来判断是否有重复的值
            while mapS[x] > 1:
                tmp = s[lhs]
                # 要移除这个值
                mapS[tmp]-=1
                lhs+=1 # 又大意了又大意了！！！
            
            # 跳出while说明此时是没有重复的，更新一下rtn
            rtn = max(rtn, i - lhs+1)

        return rtn

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.lengthOfLongestSubstring("abcabcbb")
  print(f"expect result = 3, actual result = {rtn}")

