
from typing import List

class Solution:
    #Runtime: 28 ms, faster than 100.00%
    #Memory Usage: 14.3 MB, less than 100.00%
    def jump(self, nums: List[int]) -> int:
        # 觉得这个问题本质上是interval问题，因为左边界总是小于右边界，所以这个特性使得greedy凑效
        # 0   1 2  3  4
        # 2---->|
        #     3------>|
        #       1->|
        #          1->|
        #             4
        #
        # 甚至可以计算出从nums[0]到达每个pos位置的最小值
        dp = [0 for i in range(len(nums))]
        # dp[0] = 0没毛病，不动嘛

        # 不过更新值的时机非常机智，借助不断增大的i以及end（interval的右边界，失效边界），来计数——这有点像差分数组
        end, cnt, farest = 0, 0, 0
        for i in range(len(nums)):
            # 每个位置就是一个interval，[i, i+nums[i]]
            farest = max(farest, i+nums[i])
            dp[i] = cnt # 如果只想看最后一个数的话，最终的cnt就行了；不用记录每一个cnt值
            if end == i:
                cnt += 1 #说明旧的interval能够cover的范围在本轮结束，下一轮是新的interval
                end = farest #同时更新interval的右边界，这个操作很巧妙
                # 如果i+nums[i]还被前一个interval覆盖的话，必定还不会更新cnt
                # 如果前一个interval不能覆盖i+nums[i]还被的话，max(farest, i+nums[i])必定是i+nums[i]，还是是右边界

        return dp[-1]

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.jump(nums = [2,3,1,1,4])
    print("expect result = 2, actual result = %d " % rtn )

    rtn = gua.jump(nums = [2,3,0,1,4])
    print("expect result = 2, actual result = %d " % rtn )


