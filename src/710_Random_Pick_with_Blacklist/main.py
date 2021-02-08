import random
from typing import List

class Solution:
    # Runtime: 272 ms, faster than 99.76%
    # Memory Usage: 24 MB, less than 75.06%
    '''
    为了能在O(1)之内获得特定范围内的随机数，只能是把数据存在数组中，然后rondom获得pos
    但是这里N的范围很大[1, 1e9]，如果是保存合法的数据，那么空间很大；
    一个巧妙的做法是保存blacklist里面的数据，具体办法是为这些数据进行映射，
    同时要跳过blacklist中的那些数据
    '''
    def __init__(self, N: int, blacklist: List[int]):
        self.N = N
        self.black = {}
        #last = len(blacklist)-1 # 记录最后一个合法的pos
        last = N-1 # 记录最后一个合法的pos

        for val in blacklist:
            self.black[val] = 666 # 必须先完整的加入所有的blacklist，才能进行下面的映射

        # 下面是创建一个blacklist的映射表
        for val in blacklist:
            # [N-len(blacklist),N)这个区间的数据可以跳过
            if val >= self.N - len(blacklist):
                #self.black[val] = 666 # 这里还是加一个随意值要不下面的while循环搞不定
                continue

            while last in self.black:
                last -= 1
            # 跳出while事，必定是一个合法的位置
            self.black[val] = last
            # 然后减少一个合法的位置
            last-=1

    def pick(self) -> int:
        # 现在开始生成随机数了
        pos = random.random() * (self.N - len(self.black))
        pos = int(pos) # 又忘记了python里面random是float
        # if pos in self.black:
        #     return self.black[pos]
        # return pos
        return self.black.get(pos, pos)


# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()

if __name__ == "__main__":
  N, nums = 4, [0,3]
  gua = Solution(N, nums)
  rtn = gua.pick()
  print(f"expect result = 2 or 1, actual result = {rtn}")
  print(f"expect result = 2 or 1, actual result = {rtn}")
  print(f"expect result = 2 or 1, actual result = {rtn}")
  print(f"expect result = 2 or 1, actual result = {rtn}")


