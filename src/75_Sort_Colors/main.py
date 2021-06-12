
from typing import List

class Solution:
    # Runtime: 28 ms, faster than 90.69%
    # Memory Usage: 14 MB, less than 98.23%
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        
        # 采用左右指针的办法，[0~lhs)存red，[lhs，rhs)存white。[rhs,size)存blue
        # 时间复杂度O(n)，常数空间
        # size = len(nums), i = 0
        size, i = len(nums), 0
        lhs, rhs = 0, size-1
        
        # while i < size:
        while i <= rhs: # 在运行到rhs之后就不处理了，因为rhs右侧都是2，已经排好序，再交换会出错
            if nums[i] == 0:
                nums[i], nums[lhs] = nums[lhs], nums[i]
                # lhs++ 不是C++
                lhs += 1
                i += 1
                # 由于是从左往右遍历的，因此i必定是>= lhs的
                # 当i==lhs时，与当前位置i进行交换，然后lhs和i都增加1，没毛病
                # 当i> lhs时，nums[lhs]必定不是0、且不是2，如果是0，lhs必定会右移一位
                #            nums[lhs]必定不是2，因为i已经经过了lhs，2已经交换到最右边了
                #            因此nums[lhs]只能是1，那么处理完了之后i要增加1，没毛病
            elif nums[i] == 2:
                nums[i], nums[rhs] = nums[rhs], nums[i]
                # rhs--
                rhs -= 1
                # 此时要保持i不变，因为右边还没有处理，谁知道叫缓过来的数据是0，1还是2
            else:
                # 因为用的是while，得自己操作+1，不+1的话会死循环
                i += 1

if __name__ == "__main__":
    gua = Solution()
    nums = [2,0,2,1,1,0]
    print("before sort: nums = ", nums)
    gua.sortColors(nums)
    print("after  sort: nums = ", nums)

