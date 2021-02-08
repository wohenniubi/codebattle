
import random

class RandomizedSet:
    # Runtime: 88 ms, faster than 95.53%
    # Memory Usage: 18.6 MB, less than 29.14% 

    def __init__(self):
        """
        Initialize your data structure here.
        """
        # 因为要O(1)的时间随机的获得已经存有的数，因此能在O(1)时间内完成操作的只有数组
        # 然后为了在O(1)的时间内查找到数据，当然就是哈希表了
        self.helper = {}
        self.store = []
        

    def insert(self, val: int) -> bool:
        """
        Inserts a value to the set. Returns true if the set did not already contain the specified element.
        """
        if val in self.helper: return False
        # 现在将val存入store，同时要保存它的pos
        self.helper[val] = len(self.store)
        self.store.append(val)
        return True

    def remove(self, val: int) -> bool:
        """
        Removes a value from the set. Returns true if the set contained the specified element.
        """
        if val not in self.helper: return False
        
        pos = self.helper[val]
        # 将最后一个数覆盖即将被删除的数，同时修改它在哈希表中的pos
        self.store[pos] = self.store[-1]
        self.helper[self.store[-1]] = pos
        
        # 然后去掉store中的最后一个数，同时去掉哈希表中的val
        self.store.pop(-1)
        #self.helper.remove(val)
        self.helper.pop(val, None) # del self.helper[val] 会导致error如果val不存在于helper中
        return True
        

    def getRandom(self) -> int:
        """
        Get a random element from the set.
        """
        if not self.store: return -1
        
        pos = int(random.random()* len(self.store))
        return self.store[pos]
            

# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()

if __name__ == "__main__":
  gua = RandomizedSet()
  print(f"expect result = 1, actual result = {gua.insert(1)}")
  print(f"expect result = 0, actual result = {gua.remove(2)}")
  print(f"expect result = 1, actual result = {gua.insert(2)}")
  print(f"expect result = 1 or 2, actual result = {gua.getRandom()}")
  print(f"expect result = 1, actual result = {gua.remove(1)}")
  print(f"expect result = 0, actual result = {gua.insert(2)}")
  print(f"expect result = 2, actual result = {gua.getRandom()}")


