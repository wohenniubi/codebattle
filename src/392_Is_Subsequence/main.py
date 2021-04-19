
import bisect

class Solution:
    # Runtime: 32 ms, faster than 65.46%
    # Memory Usage: 14.5 MB, less than 12.30%
    def isSubsequence(self, s: str, t: str) -> bool:
        if not s: return True   # 空集合是任何集合的子集合，包括自己
        if not t: return False  # s不为空，t为空，直接返回啦

        # 采用红黑树
        helper = {}

        # 首先完成t的数据统计，相当于KMP历史记录
        for i, c in enumerate(t):
            if c in helper:
                helper[c].append(i)
            else:
                helper[c] = [i]

        # 现在开始排查s, prev是t里面的开始位置，每次找的位置肯定都大于等于prev，因为index本身就是sorted的
        prev, size = 0, len(t)
        for i, c in enumerate(s):
            if c not in helper:
                return False
            else:
                # 当c存在于t里面时，查找t里面c这个字符>=当前位置的位置
                pos = bisect.bisect_left(helper[c], prev) # 相当于lower_bound
                if pos == len(helper[c]): #别大意了，pos是helper[c]的index
                    # 没有找到合适的位置
                    return False
                else:
                    # 找到合适的位置
                    if i+1 == len(s):
                        return True # 已经是最后一位啦，说明找到了
                    else:
                        prev = helper[c][pos] +1 # 下次从t中这个位置的右侧开始查找s的字符
            # end of if-else s数组自动右移1位

        # end of for循环，此时都没有返回，肯定不是子集
        return False

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.isSubsequence(s = "abc", t = "ahbgdc")
    print("expect result = True, actual result = ", rtn)

    rtn = gua.isSubsequence(s = "axc", t = "ahbgdc")
    print("expect result = False, actual result = ", rtn)



