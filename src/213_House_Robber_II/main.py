
from typing import List

class Solution:
    # Runtime: 32 ms, faster than 63.16%
    # Memory Usage: 14 MB, less than 94.12%
    def rob(self, nums: List[int]) -> int:
        # 和198题一样思路，只不过划分为多个dp数组，一定抢[0]，一定不抢[0]情况下的最大值
        size = len(nums)
        rob0 = [0] * size
        nrob0 = [0] * size
        
        # 初始化
        rob0[0] = nums[0]
        if size > 1:
            rob0[1] = nums[0]
            nrob0[1] = nums[1]
        
        # 然后分别运算
        for i in range(2,size-1): #对于rob0的更新，只到nums[size-2]
            rob0[i] = max(rob0[i-1], rob0[i-2] + nums[i])
        
        for i in range(2,size): #对于nrob0的更新，可以到nums[size-1]
            nrob0[i] = max(nrob0[i-1], nrob0[i-2] + nums[i])

        # 最后从两者里面取较大者
        return max(rob0[size-2], nrob0[size-1])

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.rob(nums=[2,3,3])
    print("expect result = 3, actual result = ", rtn)

    rtn = gua.rob(nums=[1,2,3,1])
    print("expect result = 4, actual result = ", rtn)

    rtn = gua.rob(nums=[0])
    print("expect result = 0, actual result = ", rtn)


