
class Solution:
    def maxA(self, N: int) -> int:
        # 一看就是dp问题，来吧想状态方程，其中dp[i][j][k]表示剩余操作数，屏幕A个数，粘贴板A个数
        memo = {}

        # 以下操作会超时，因为复杂度与三个状态有关O(n*screenA*bufferA)
        # 而随着screenA和bufferA的增大，即使有memo，复杂度也很高，简单dp失败，需要另辟蹊径
        def getMaxA1(n: int, screenA: int, bufferA: int) ->int:
            # 返回条件TODO
            # if N <= 3: return N
            if n == 0: return screenA

            if (n, screenA, bufferA) in memo:
                return memo[(n, screenA, bufferA)]

            # 开始计算,这里其实就是三维矩阵，getMax展开之后本质还是从N=1开始算的
            rtn = max(getMaxA(n-1, screenA+1, bufferA), # 操作1，按下‘A’
                     getMaxA(n-1, screenA+bufferA, bufferA), # 操作4，按下Ctrl+V粘贴
                    getMaxA(n-2, screenA, screenA)) # 操作2+3，连用才会有最大值

            memo[(n ,screenA, bufferA)] = rtn
            return rtn

        # 变量n最多为N，但是screenA和bufferA最多为多少我们很难计算，复杂度起码也有 O(N^3)，会超时
        #return getMaxA(N, 0, 0)

        # 仔细思考一个问题，greedy来看，肯定是全选+复制+粘贴会产生更多的A，因此这种情pattern
        # 应该形如C-A, C-C, (中间可能是C-A, C-C或者全部是C-V)... C-V；不过敏锐的感觉到，由于复制粘贴至少要多2次操作C-A，C-C
        # 可以料想在n很小的时候，比如n<=6，此时直接按A的个数大于等于复制粘贴之后A的个数，因此直接把复制粘贴合为一种操作，
        # 另一种操作是直接A，因此状态可以减少
        #Runtime: 36 ms, faster than 54.74%
        #Memory Usage: 14.3 MB, less than 63.50%
        dp = [0 for i in range(N+1)]

        for i in range(1,N+1):
            dp[i] = dp[i-1]+1 # 选择直接A就是在上一级的基础上+1，这也算是对dp[i]进行初始化

            # 这里j表示的是粘贴C-V所在的操作数，它前面至少要有C-A，C-C才可能超过直接A，所以C-V要从第三位出发，且不超过i
            for j in range(2,i):
                tmp = dp[j-2] * (i-j+1)
                # 这里j是C-A，C-C结束的次数，C-A拷贝的是C-A前一次结束后的A个数，因此就是j-2（j-1对应C-A）
                # 然后保证j-2为非负，所以j从2开始；然后i是C-V的次数，i-j就是复制的次数；
                # 复制后 + 复制之前的1次，总共i-j+1次，因此A的总数变成dp[j-2]*(i-j+1)
                dp[i] = max(dp[i], dp[j-2] * (i-j+1))
        return dp[N]

if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.maxA(N = 3)
    print("expect result = 3, actual result = %d " % rtn )

    rtn = gua.maxA(N = 6)
    print("expect result = 6, actual result = %d " % rtn )

    rtn = gua.maxA(N = 7)
    print("expect result = 9, actual result = %d " % rtn )

