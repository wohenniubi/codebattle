
from typing import List

class Solution:
    # Runtime: 228 ms, faster than 50.43%
    # Memory Usage: 15.6 MB, less than 84.00%
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        # 循环不可怕，就多转一圈嘛
        size = len(nums)
        rtn = [-1] * size
        st = []

        # 由于可以环回，最坏情况是nums[size-1]这个值的右边较大值是nums[size-2]，因此总长度是2*size-1
        for i in range(2*size-1):
            j = i % size #防止越界
            while st and nums[st[-1]] < nums[j]:
                # 此时需要pop较小值，同时更新返回值
                if rtn[st[-1]] == -1:
                    rtn[st[-1]] = nums[j]
                st.pop(-1)
            # 跳出while循环表示st为空，或者st[-1]>=nums[j]，那么此时就赛进st成为新的st[-1]
            st.append(j)

        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.nextGreaterElements(nums=[1,2,1])
    print("expect result = [2,-1,2], actual result = ", rtn)

