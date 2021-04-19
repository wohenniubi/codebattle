
class Solution:
    # Runtime: 32 ms, faster than 58.27%
    # Memory Usage: 14.2 MB, less than 65.07%
    def isValid(self, s: str) -> bool:
        st = []
        
        # 遍历数组，然后借助一个stack就可以搞定
        size = len(s)
        
        def match(a, b)->bool:
            if a == '{': return b == '}'
            if a == '(': return b == ')'
            return a == '[' and b == ']'
        
        for i in range(size):
            if s[i] in ['{', '(', '[']:
                st.append(s[i]) # 压栈就好了
            else: # 那就是['}', ')', ']']:
                if not st:
                    return False
                if not match(st.pop(-1), s[i]):
                    return False
        
        # 最后要完全匹配，st必然为空
        return True if not st else False
            
if __name__ == "__main__":
    gua = Solution()
    rtn = gua.isValid(s="()")
    print("expect result = True, actual result = ", rtn)

    rtn = gua.isValid(s=r"()[]{}")
    print("expect result = True, actual result = ", rtn)

    rtn = gua.isValid(s=r"(]")
    print("expect result = False, actual result = ", rtn)

    rtn = gua.isValid(s=r"([)]")
    print("expect result = False, actual result = ", rtn)

    rtn = gua.isValid(s=r"{[]}")
    print("expect result = True, actual result = ", rtn)


