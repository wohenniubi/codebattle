from typing import List

class Solution:
    def findTargetSumWays1(self, nums: List[int], S: int) -> int:
        # 又忘记这道题怎么做了，本质上是个决策树问题，然后保证到达决策树叶子结点时sum等于target，或者说与target的相差值等于0
        # 那么就比较容易想到回溯算法+memo数组，然后再考虑dp做法；
        # 对于回溯算法，不知道如何下手的话，先暴力写个递归的框架，再加入memo数组
        
        result = 0
        def bruteforce(nums: List[int], pos: int, diff: int):
            global result
            if pos == len(nums):
                # 如果到达leaf节点，且与targetsum的差异值为0，那么result+1，找到一个possible solution
                result += (1 if diff == 0 else 0)
                return
            
            # 选择1，使用+，那么需要从diff中移除这个值
            bruteforce(nums, pos+1, diff-nums[pos])
            # 原本需要revert策略，但是没有对原始数据进行操作，所以就不用revert了
            
            # 选择2: 使用-，需要给diff加上这个值
            bruteforce(nums, pos+1, diff+nums[pos])
            return
        
        # 时间复杂度是O(2^n)，肯定不pass
        bruteforce(nums, 0, TargetSum)
        return result
        
    # Runtime: 372 ms, faster than 44.64%
    # Memory Usage: 36.4 MB, less than 13.11%
    def findTargetSumWays2(self, nums: List[int], S: int) -> int:
        memo = {}
        # Runtime: 372 ms, faster than 44.64%
        # Memory Usage: 36.4 MB, less than 13.11%
        def backtrackMemo(nums: List[int], pos: int, diff: int) -> int:
            if pos == len(nums):
                return int(diff == 0)

            # 使用 (pos, diff) 作为key，python独有，其他语言的话要把pos和diff改写一下
            key = (pos, diff)
            if key in memo:
                return memo[key]
            
            rtn = 0
            #选择1，选择+
            rtn += backtrackMemo(nums, pos+1, diff-nums[pos]) # 别大意写错字啊backtraceMemo
            #选择1，选择-
            rtn += backtrackMemo(nums, pos+1, diff+nums[pos])
            
            # 由于这两种选择都代表不一样结果，即使子数组部分的值相同，也不代表重复的选择，所以可以加扰叠加到rtn
            memo[key] = rtn
            return rtn
        return backtrackMemo(nums, 0, S) # TargetSum
        
    # 方法3: 有点小trick，转换之后采用背包问题框架来解决
    # 在nums中找到一部分元素用+，一部分元素用-，然后凑出TargetSum，就相当于 A-B = S
    def findTargetSumWays(self, nums: List[int], S: int) -> int:
        # 那么变形之后得到 A + B = S + 2B，左侧是T = sum(nums)
        # 所以就等价于找到一部分正的元素，使得其sum*2等于T-S，这不就是背包问题吗
        diff = sum(nums) - S # T-S
        # if diff%2: 大意了，别忘记diff < 0的情况
        if diff%2 or diff < 0: 
            return 0  # 如果是奇数，sum*2肯定不为奇数，说明凑不出目标值S，直接返回

        diff = int(diff/2) # diff /= 2 别大意啊，python里面这是float
        # 还好题目说S的值不超过20，len(nums)不超过1000
        # 这里的dp[i][j]表示总共i个物品、恰好可以凑够容量为j的背包的方法数目，一会儿再进行空间压缩
        dp = [[0 for j in range(diff+1)] for i in range(len(nums)+1)]
        # 行列都多一个，这样的好处在于，避免讨论第0个物品重量是否为0、是否符合背包大小为0的情况

        # 然后初始化，第一列dp[i][0]全部是1，认为背包大小为0时为装满，即只有不选这1种选法，没毛病
        for i in range(len(nums)+1): dp[i][0] = 1

        # 现在开始更新，从上到下，从左到右
        for i in range(1, len(nums)+1):
            # for val in range(1, diff+1): # 这里非常隐蔽！要允许val=0的情况，因nums[i]可能为0，故背包从0开始
            for val in range(0, diff+1):
                if val >= nums[i-1]:
                    # 能够装下物品时，分为装或者不装两个选择
                    # dp[i][val] = dp[i-1][val - nums[i-1]] or dp[i-1][val] # 这是True或False的情况
                    dp[i][val] = dp[i-1][val - nums[i-1]] + dp[i-1][val] # 选或不选肯定是不同的策略，所以相加
                else:
                    dp[i][val] = dp[i-1][val]
        # 最后返回的应该是最后一列的等于1的个数吧—— 不是这样的
        # return sum([row[-1] for row in dp])
        return dp[len(nums)][diff] # 右下角dp[-1][-1]
        
if __name__ == "__main__":
    gua = Solution()
    rtn = gua.findTargetSumWays(nums = [1, 0], S = 1)
    print("expect result = 2, actual result = %d " % rtn )

    rtn = gua.findTargetSumWays(nums = [1, 1, 1, 1, 1], S = 3) # 这种写法必须用S，而不是任意的targetSum，这个好
    print("expect result = 5, actual result = %d " % rtn )

    rtn = gua.findTargetSumWays(nums = [1], S = 1)
    print("expect result = 1, actual result = %d " % rtn )


