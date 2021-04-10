from typing import List
import heapq

class Solution:
    # Runtime: 116 ms, faster than 87.01% of Python3 online submissions for Sliding Window Median.
    # Memory Usage: 16 MB, less than 40.78%
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        # 本来没想法的，回看了一下239题，再试一下

        # 两个priority queue，python默认是min heap
        loheap = []
        hiheap = []

        memo = {} # 用来存储过期时间
        for i in range(k):
            heapq.heappush(loheap, -nums[i])
        # 然后将其中的一般分配到hiheap，这就是初始平衡状态
        for i in range(k//2):
            val = -heapq.heappop(loheap)
            heapq.heappush(hiheap, val)

        rtn = []
        # for i in range(k, len(nums)): 如果使用for的话，后还差一次计算median
        i = k # 因此自己控制索引，小心点哟
        while True:
            # 现在每次执行都会产生一个median
            # rtn.append(-loheap[0] if k%2 else hiheap[0])
            rtn.append(-loheap[0]*1.0 if k%2 else (hiheap[0]- loheap[0])/2 )
            if i >= len(nums):
                break
            ibk = i
            i+=1 # 写在这里免得太远了忘记了

            # 现在设置要被弹出的值，和加入的值，还有初始balance值
            outval, inval, balance = nums[ibk-k], nums[ibk], 0

            # 忘记了弹出值对balance的影响，如果弹出的数在左半，那么弹出之后左半变轻了，所以balance<0
            balance += (-1 if outval <= -loheap[0] else 1)
            memo[outval] = memo.get(outval, 0) + 1 #记录一下要失效的值

            # 这里是新加入的值对于balance的影响
            if loheap and inval > -loheap[0]:
                heapq.heappush(hiheap, inval)
                balance -= 1
            else:
                heapq.heappush(loheap, -inval)
                balance += 1

            # 已经保证左右半的顺序了，但是还要让左右两半平衡才好计算median
            if balance > 0:
                # 要把左边的放到右边
                heapq.heappush(hiheap, -loheap[0])
                heapq.heappop(loheap)
                balance -= 1

            if balance < 0: # 这里不能用elif，因为balance可能小于-1
                # 要把右边的放在左边
                heapq.heappush(loheap, -hiheap[0])
                heapq.heappop(hiheap)
                balance += 1

            # 在前面保证了顺序，且balance的情况下，现在要解决失效的问题了
            # 即使有相同的val，且其中一个失效一个不失效，也不会影响，因为已经是平衡的情况
            # 平衡情况就是左半个数 >= 右半个数
            while memo.get(-loheap[0], 0):
                memo[-loheap[0]] -= 1
                heapq.heappop(loheap)

            # while memo.get(hiheap[0], 0): 好贱，居然这里要判断hi是否为空，因为右半总是要少一些
            while hiheap and memo.get(hiheap[0], 0):
                memo[hiheap[0]] -= 1
                heapq.heappop(hiheap)

        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.medianSlidingWindow(nums=[1,2], k = 1)
    print("expect result = [1,2], actual result = ", rtn)

    rtn = gua.medianSlidingWindow(nums=[1,2,3,4,2,3,1,4,2], k = 3)
    print("expect result = [2,3,3,3,2,3,2], actual result = ", rtn)

    rtn = gua.medianSlidingWindow(nums=[1,3,-1,-3,5,3,6,7], k = 3)
    print("expect result = [1,-1,-1,3,5,6], actual result = ", rtn)


