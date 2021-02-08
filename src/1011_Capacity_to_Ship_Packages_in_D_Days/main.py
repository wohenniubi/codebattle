from typing import List

class Solution:
    def shipWithinDays(self, weights: List[int], D: int) -> int:
        def canTakeAll(weights: List[int], D: int, C: int) -> bool:
            cnt, days = 0, 0
            for i in range(len(weights)):
                cnt += weights[i]
                if cnt > C:
                    # 更新cnt和lhs
                    cnt = weights[i]
                    days+=1
            # 跳出循环之后还要再根据cnt算一算
            if cnt:
                days+=1
            return True if days<= D else False

        # 使用二分查找，最小的值肯定是货物里面最大的那个值，要不然一个货都装不了，不过
        # 貌似可以再稍微优化一下，是sum/D的平均值；最大的值肯定是所有货物的值
        lhs, rhs = max(weights), sum(weights)
        
        #rhs+=1
        while lhs <= rhs:
            mid = lhs + int((rhs - lhs)/2)
            # 如果和mid的值相等的话，
            if canTakeAll(weights, D, mid):
                rhs = mid-1
            else:
                lhs = mid+1
                        
        return lhs
        
if __name__ == "__main__":
  gua = Solution()
  weights = [1,2,3,4,5,6,7,8,9,10]
  rtn = gua.shipWithinDays(weights, D = 5)
  print(f"expect result = 15, actual result = {rtn}")

  weights = [3,2,2,4,1,4]
  rtn = gua.shipWithinDays(weights, D = 3)
  print(f"expect result = 6, actual result = {rtn}")

  weights = [1,2,3,1,1]
  rtn = gua.shipWithinDays(weights, D = 4)
  print(f"expect result = 3, actual result = {rtn}")

