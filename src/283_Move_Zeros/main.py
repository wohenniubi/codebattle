
from typing import List

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        还是老生常谈，快慢索引
        """
        
        lhs = 0 # 该位置存的是即将被填上非0数据的pos
        for i in range(len(nums)):
            if nums[i] == 0:
                # 那么该位置不需要处理，进入下一个
                pass
            else:
                # 将该位置填入lhs
                nums[lhs] = nums[i]
                lhs += 1
        
        # 当结束for之后，lhs可能停在len(nums)，这表明没有0
        # 其他情况下都需要赋值为0
        while lhs < len(nums):
            nums[lhs] = 0
            lhs+=1 # 大意了大意了！！！
        
        return


if __name__ == "__main__":
    gua = Solution()
    nums = [0,1,0,3,12]
    print(nums)
    gua.moveZeroes(nums)
    print(nums)

    nums = [3,1,12]
    print(nums)
    gua.moveZeroes(nums)
    print(nums)

