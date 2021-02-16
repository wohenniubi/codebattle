
from typing import List

class Solution:
    # Runtime: 1088 ms, faster than 5.09%
    # Memory Usage: 16.2 MB, less than 9.74%
    def combine1(self, n: int, k: int) -> List[List[int]]:
        '''
        1 [1,2] [1,3] [1,4]
        2 [2,1] [2,3] [2,4]
        3 [3,2] [3,1] [3,4]
        4 [4,2] [4,3] [4,1]
        我想了一下，没有想透彻，不过展开上面的操作之后发现了规律：
        第一行取后3个，第二行取后2个，第三行取后1个，第四行一个都不取
        则总数等于6个，正好是C42组合的个数，fancy
        '''
        self.rtn = []

        def traverse(n: int, pos: int, k: int, cnt: int, path: List[int]) ->None:
            if pos == k:
                # self.rtn.append([x for x in path[0:k]])
                self.rtn.append(path[:k].copy())
                return

            # 来哇，现在是状态和决策
            for i in range(pos, n):
                # if i < cnt: continue
                if i < cnt+pos: continue

                # push操作
                path[i], path[pos] = path[pos], path[i]
                # 当top = nums[0] = 1    [1,2,3,4]
                #   index = 1,2,3 = 2,3,4
                #   [1,2,3,4]
                #   [1,3,2,4]
                #   [1,4,3,2]
                # 然后只截取[0,2)之间的list，得到[1,2],[1,3],[1,4]
                # 当top = nums[1] = 2    [2,1,3,4]
                #   index = 2, 3 = 3,4  要跳过1次
                #
                # [1,2,3,4] -> [1,2,3,4]
                traverse(n, pos+1, k, cnt, path)
                cnt+=1 # 这样下一次就会只进行cnt次

                # pop操作
                path[i], path[pos] = path[pos], path[i]
            return

        path = [x+1 for x in range(n)]
        traverse(n, 0, k, 0, path)
        return self.rtn

    # 往上的另一种做法，思路一样，只不过path先是空的，往里面添加直到满足长度k
    def combine(self, n: int, k: int) -> List[List[int]]:
        # arr = [i+1 for i in range(n)]
        res = [] # 直接使用局部变量gencomb也可以访问哟
        def gencomb(st,curList,k):
            if k==0:
                res.append(curList.copy())
                return

            for i in range(st,n-k+2):
                curList.append(i)
                gencomb(i+1,curList,k-1)
                curList.pop()

        gencomb(1,[],k)
        return res

if __name__ == "__main__":
  gua = Solution()
  # nums = [1,2,3]
  # rtn = gua.permute(nums)
  # print(rtn)
  # rtn = gua.subsets([1,2,3])
  rtn = gua.combine(n=4, k =2)
  print(rtn)

