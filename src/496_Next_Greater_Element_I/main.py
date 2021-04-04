
from typing import List

class Solution:
    # Runtime: 52 ms, faster than 46.37%
    # Memory Usage: 14.6 MB, less than 43.05%
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        # 首先想一下单调栈的模版，只有一个数组，但是本题有两个数组
        # 不过nums1是nums2的子集合，且是unique数组，所以等效就是一个数组
        dp = {}
        for i in range(len(nums1)):
            dp[nums1[i]] = i

        rtn, st = [-1 for num in range(len(nums1))], [] # 如果递增遍历，那么单调栈里面存的是index

        size = len(nums2)
        for i in range(size):
            # 对于st[-1] >= nums[i]的情况都不会pop，所以=不在while条件中
            # while st and st[-1] < nums2[i]: 口口声声说st是index，怎么忘记转换成值
            while st and nums2[st[-1]] < nums2[i]:
                # pop最后一个元素，同时利用pop出来的index，修改这个位置的原始值
                if nums2[st[-1]] in dp: # 别忘记这个啊，因为nums1和nums2不同
                  rtn[dp[nums2[st[-1]]]] = nums2[i]
                st.pop(-1)

            # while结束值可能有两种情况，st为空；或者st[-1]>=当前nums[i]
            # 此时后者加入st其中成为新的st[-1]，注意加入index更方便
            st.append(i)

        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.nextGreaterElement(nums1=[1,3,5,2,4], nums2=[5,4,3,2,1])
    print("expect result = [-1,-1,-1,-1,-1], actual result = ", rtn)

    rtn = gua.nextGreaterElement(nums1=[4,1,2], nums2=[1,3,4,2])
    print("expect result = [-1,3,-1], actual result = ", rtn)

    rtn = gua.nextGreaterElement(nums1=[2,4], nums2=[1,2,3,4])
    print("expect result = [3,-1], actual result = %d ", rtn)


