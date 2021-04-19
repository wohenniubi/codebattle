
from typing import List

class Solution:
    # Runtime: 64 ms, faster than 6.60%
    # Memory Usage: 14.6 MB, less than 5.01%
    def pancakeSort(self, arr: List[int]) -> List[int]:
        # 看了一下参考答案，比我自己想的BST暴力求解要好；基本原理是采用了greedy的思路，尽量将最大值放到最右边
        # 状态就是arr的范围，然后选择就是k个翻翻转位置；然后当翻好一个最大的饼之后，问题规模减小1，因为需要记录路径path，用递归好一些

        rtn = []

        def revSubarr(arr: List[int], bgn: int, end: int):
            # 来练习一下reverse [bgn, end)
            size = end - bgn
            if size <= 1:
                return # 空或者1就不交换了

            size = size//2
            # 0 ---- end-1
            # 1 ---- end-2
            # 到<size//2的位置终止；
            # 因为size=3时，交换0和2，然后交换1和1
            # 因为size=2时，交换0和1
            for i in range(size):
                tmp = arr[bgn+i]
                arr[bgn+i] = arr[end-1-i]
                arr[end-1-i] = tmp
            return

        def sortSubarr(arr: List[int], n :int):
            # 基本思路找到[0,n)之间的最大值，然后翻转到第0位，再翻转整个[0,n)
            # 返回条件TODO
            if n <= 1:
                return  # n是逐渐减小的，所以此时返回就好

            pos = 0
            # 这个for 循环找到最大的值的pos
            for i in range(1,n):
                if arr[i] > arr[pos]:
                    pos = i

            if pos != n-1:
                if pos != 0: # 大意了啊！只有在不等于第0位时才交换
                    # 此时翻转arr[0]到arr[pos]这部分，让最大值变到第一位
                    revSubarr(arr, 0, pos+1)
                    rtn.append(pos+1)
                # 再翻转arr[0]到arr[n]这部分，让最大值变到最后一位
                revSubarr(arr, 0, n)
                rtn.append(n)

            # sortSubarr(arr, 0, n-1) #缩小问题规模
            sortSubarr(arr, n-1) #缩小问题规模
            return

        sortSubarr(arr, len(arr))
        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.pancakeSort(arr=[3,2,4,1])
    print("expect result = [3,4,2,3,2], actual result = ", rtn)

    rtn = gua.pancakeSort(arr=[1,2,3])
    print("expect result = [], actual result = ", rtn)


