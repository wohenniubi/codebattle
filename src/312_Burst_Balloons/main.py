
from typing import List

class Solution:
    # Runtime: 8344 ms, faster than 49.79%
    # Memory Usage: 19.8 MB, less than 86.32%
    def maxCoins(self, nums: List[int]) -> int:
        # 看似简单，但是状态不好找，因为要去除某个气球，这不仅会对List进行频繁操作
        # 而且不容易利用历史信息；想了一下，要不然倒着往前计算最大值
        # dp[i][j]表示[i.j]这个区间的最大coins值，首先从i==j开始，基本思路正确，具体操作有技巧
        size = len(nums) # nums = [3,1,5,8], size = 4
        nums.insert(0,1) # 前后各补一个虚拟气球
        nums.append(1)
        
        dp = [[0 for j in range(size+2)] for i in range(size+2)]
        # dp[i][j]定义为(i,j)之间的气球戳爆后的sum，最终求的是dp[0][size+1]，表示[1,size]的气球值
        # 不需要初始化dp[i][i]。因为按照dp的定义，相当于(i,i)之间的气球值，这里只有寂寞
        
        # 更新i和j，从对角线更新到右上角
        # for i in range(size+1, -1, -1): # i递减，下限为0好理解，i初始值为size+1，就是最后一列(不过这一列的j loop是空的)
        for i in range(size, -1, -1): # i递减，下限为0好理解，i初始值为size+1，就是最后一列(不过这一列的j loop是空的)，少算这一行也行
            for j in range(i+1, size+2): # i+1好理解，小于size+2才可以达到虚拟气球之后的最后一个index
                for k in range(i+1,j): # 非常经典的设置，k的意义是(i,j)序列之中最后一个剩下的气球，那么k就只能取[i+1,j-1]
                    dp[i][j] = max(dp[i][j], # 因为是从下一行往上一行逐行计算，可能会访问到先前的dp[i][j]值，得使用最大值才能防止被小值覆盖
                                  dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j])
                    # 非常巧妙，既然k是最后一个被戳的，说明[i+1,k)和(k,j)都没有了，于是nums[k]紧邻nums[i]和nums[j]，符合题目条件
        # for sublen in range(2, size+1):
        #     for i in range(size-sublen+1):
        #         j = i+sublen-1 
        #         # 现在计算dp[i][j]的值，[3,1]这个区间既可以打左边变成[1]
        #         # 也可以打右边使得变为[3]，而[1]和[3]的最大coin数是知道的
        #         lhs = 1 if i-1 < 0 else nums[i-1]
        #         rhs = 1 if j+1 >= size else nums[j+1]
        #         # 疏忽了，需要把中间的都遍历一遍
        #         dp[i][j] = max(lhs*nums[i]*nums[i+1] + dp[i+1][j],  # 打左边
        #                     dp[i][j-1] + nums[j-1]*nums[j]*rhs) # 打右边
        
        return dp[0][size+1]
                
if __name__ == "__main__":
    gua = Solution()
    # rtn = gua.isMatch(s = "aaa", p = "ab*ac*a")
    rtn = gua.maxCoins(nums = [3,1,5,8])
    print("expect result = 167, actual result = %d " % rtn )

    rtn = gua.maxCoins(nums = [1,5])
    print("expect result = 10, actual result = %d " % rtn )

