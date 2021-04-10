
import bisect
import heapq

class MedianFinder:
    # 采用了priorityq，python默认是按照greater排序，即min heap; C++默认是less排序，是max heap
    def __init__(self):
        """
        invariant: len(left_heap) + 1 >= len(right_heap) >= len(left_heap)
        """
        self.left_heap = [] # max heap
        self.right_heap = [] # min heap

    def addNum(self, num: int) -> None:
        if len(self.left_heap) == len(self.right_heap):
            heapq.heappush(self.left_heap, - num)
            top = - heapq.heappop(self.left_heap)
            heapq.heappush(self.right_heap, top)
        else:
            heapq.heappush(self.right_heap, num)
            low = heapq.heappop(self.right_heap)
            heapq.heappush(self.left_heap, - low)

    def findMedian(self) -> float:
        if len(self.left_heap) == len(self.right_heap):
            first = - self.left_heap[0]
            second = self.right_heap[0]
            return (first + second) / 2.0
        else:
            return self.right_heap[0]


class MedianFinder2:
    #Runtime: 252 ms, faster than 27.00%
    #Memory Usage: 25.8 MB, less than 24.10%
    # 这里可以的改进是，不一定要让左右两个bisect保持完美的递增order
    # 只要保证左半的bisect个数>=右半的bisect个数，就可以了；然后就是看lhalf[-1]和rhalf[0]这两个中间值
    def __init__(self):
        """
        initialize your data structure here.
        """
        self.lhalf = []
        self.rhalf = []

    def addNum(self, num: int) -> None:
        # 总是先加入到左边
        pos = bisect.insort_right(self.lhalf, num)
        
        # 然后保证左右两半的顺序
        if len(self.rhalf) and self.lhalf[-1] > self.rhalf[0]:
            bisect.insort_right(self.rhalf, self.lhalf[-1])
            self.lhalf.pop(-1)
        
        # 现在开始维护两个分支的数量大小
        if len(self.lhalf) > len(self.rhalf) + 1:
            bisect.insort_right(self.rhalf, self.lhalf[-1])
            self.lhalf.pop(-1)
        elif len(self.lhalf) < len(self.rhalf):
            bisect.insort_right(self.lhalf, self.rhalf[0])
            self.rhalf.pop(0)

    def findMedian(self) -> float:
        if not len(self.lhalf): return 0
        
        if len(self.lhalf) > len(self.rhalf):
            return self.lhalf[-1]
        else:
            return (self.lhalf[-1] + self.rhalf[0])/2

if __name__ == "__main__":
    gua = MedianFinder()
    nums = [2,7,9,4,4]

    for num in nums:
      gua.addNum(num)
      rtn = gua.findMedian()
      print(rtn, end = ", ")

    print("") # 不加这一行的话会在shell里面的最后出现一个%

