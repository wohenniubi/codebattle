
from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        # 我想到的是快慢索引，慢索引始终指向的是较小的那个唯一的值
        # 来吧战个痛快
        size = len(nums)
        if size < 2: return size #空数组和长度为1都不会有重复

        lhs = 0
        for i in range(len(nums)):
            # if nums[i] = nums[lhs]: 超级大意，居然写成=了
            if nums[i] == nums[lhs]:
                # 当等于时，保持lhs不动，然后被nums[i]覆盖
                # 尽管对于nums[0]来说有点重复(因为i==lhs)
                # 但是当i不等于lhs时，这样的操作就有意义了
                nums[lhs] = nums[i]
            else:
                assert(nums[i] > nums[lhs])
                # 因为是sorted的，因此必然没有nums[i]<nums[lhs]的情况
                lhs += 1
                nums[lhs] = nums[i]

        # 清理掉后续无效的元素
        # [1,1,2]
        # 0#    lhs = 0  [1,1,2]
        # 1#    lhs = 0  [1,1,2]
        # 2#    lhs = 1, [1,2,2]
        cnt = size-(lhs+1)
        while cnt > 0:
            nums.pop(-1)
            cnt-=1

        return lhs+1 #lhs是0-index

        # [0,0,1,1,1,2,2,3,3,4]
        # 0#    lhs = 0
        # 1#    lhs = 0
        # 2#    lhs = 1, [0,1,1,1,1,2,2,3,3,4]
        # 3#    lhs = 1
        # 4#    lhs = 1
        # 5#    lhs = 2, [0,1,2,1,1,2,2,3,3,4]
        # 6#    lhs = 2
        # 7#    lhs = 3, [0,1,2,3,1,2,2,3,3,4]
        # 8#    lhs = 3
        # 9#    lhs = 4, [0,1,2,3,4,2,2,3,3,4]
        # size = 10, lhs+1 = 5



