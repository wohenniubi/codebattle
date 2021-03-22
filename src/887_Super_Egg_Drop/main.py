
class Solution:
    #Runtime: 964 ms, faster than 28.43%
    #Memory Usage: 20.7 MB, less than 51.57%
    def superEggDrop(self, k: int, n: int) -> int:
        # 还是dp问题，状态是剩余鸡蛋个数K，当前所在的楼层数区间[1,n]
        # 但是留意到在[i,i]和[i+1,n]扔鸡蛋其实没有本质区别，所以楼层区间就简化为楼层数n
        
        memo = {}
        def dp(k: int, n: int) -> int:
            # 返回条件TODO
            if k == 1: return n # 只有一个蛋，那没办法只好遍历
            if n <= 1: return n # 1层时只礽1次就可以判断f是0还是1
            
            if (k, n) in memo:
                return memo[(k, n)]
            
            # 然后选择是在可能的楼层都礽一遍，这样才能确定任何位置的f——时间复杂度O(k*n*n)，过不了
            rtn = float('INF')
            # # for i in range(1, n): 大意了，要遍历1到n 
            # for i in range(1, n+1): 
            #     # 在第i层楼扔鸡蛋，两种结果，蛋碎(那么f肯定比i小)和不碎(那么f肯定比i大)，要选择其中最差的结果再加1
            #     rtn = min(rtn, max(dp(k-1, i-1), # 蛋碎，1到i-1楼，共i-1楼
            #                        dp(k, n-i)) + 1) # i+1到n楼，共有n-i楼
            lhs, rhs = 1, n
            while lhs <= rhs:
                i = lhs + (rhs-lhs)//2 # int((rhs-lhs)/2)
                t1 = dp(k-1, i-1) # 该函数是i的增函数
                t2 = dp(k, n-i) # 是i的递减函数
                if t1 < t2:
                    # 说明i点还在最优点的左边，那么提升lhs
                    lhs = i+1
                    rtn = min(rtn, t2+1)
                elif t1 > t2:
                    # i点选在最优点的右边，那么减少rhs
                    rhs = i-1
                    rtn = min(rtn, t1+1)
                else:
                    #lhs = rhs = i
                    rhs = i-1 # 随便都可以，不过写成这样就可以合并一个分支
                    rtn = min(rtn, t2+1)
            
            memo[(k, n)] = rtn
            return rtn
        
        return dp(k, n)
        
if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.superEggDrop(k = 1, n = 2)
    print("expect result = 2, actual result = %d " % rtn )

    rtn = gua.superEggDrop(k = 2, n = 6)
    print("expect result = 3, actual result = %d " % rtn )

    rtn = gua.superEggDrop(k = 3, n = 14)
    print("expect result = 4, actual result = %d " % rtn )

    rtn = gua.superEggDrop(k = 4, n = 2000)
    print("expect result = 16, actual result = %d " % rtn )


