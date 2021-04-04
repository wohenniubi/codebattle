
from typing import List

class Solution:
    # Runtime: 528 ms, faster than 41.57%
    # Memory Usage: 15.7 MB, less than 55.26%
    def stoneGameII(self, piles: List[int]) -> int:
        # 基本模型就是minMax，对于每个人来讲，状态只有2个，M和当前剩余piles(起始位置)
        # 但是由于M是增长的，所以还是先用递归+memo
        memo = {}

        # 这个dp存储的是差值的最大值
        def dp(piles: List[int], M: int, bgn: int) -> int:
            # 返回条件TODO
            size = len(piles)
            if bgn >= size: return 0

            if (M, bgn) in memo:
                return memo[(M, bgn)]

            # 现在开始处理选择，复杂度O(M*len*len)，而M是max(M,X)，X<=len
            # 所以复杂度O(len^3)，而len <= 100，应该还可以接受
            rtn, tmp = float('-inf'), 0
            # for i in range(1,2*M+1): # 要小心剩余piles的数量，不要越界了
            # for i in range(1,min(2*M+1, size-bgn)): # 又大意了啊！两个长度之间取最小
            for i in range(1,min(2*M, size-bgn)+1): # +1是为了取右边界
                tmp += piles[bgn + i-1]
                rtn = max(rtn, tmp - dp(piles, max(i,M), bgn+i))

            memo[(M, bgn)] = rtn
            return rtn

        diff = dp(piles, 1, 0) # A-B
        sumP = sum(piles) # A+B
        return (diff + sumP)//2

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.stoneGameII(piles=[2,7,9,4,4])
    print("expect result = 10, actual result = ", rtn)

    rtn = gua.stoneGameII(piles=[1,2,3,4,5,100])
    print("expect result = 104, actual result = ", rtn)

