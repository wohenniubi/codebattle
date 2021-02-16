
# 这里保存4个list，便于查询某个2D位置是否出现冲突
rows, cols, llas, rlas = [], [], [], []

class Solution:
    # Runtime: 76 ms, faster than 51.34% 
    # Memory Usage: 14.4 MB, less than 40.75%
    def totalNQueens1(self, n: int) -> int:
        global rows, cols, llas, rlas
        rows = [x>n for x in range(n)]
        cols = [x>n for x in range(n)]
        # llas = [x>n for x in range(n)] 大意了
        # rlas = [x>n for x in range(n)] 大意了
        llas = [x>2*n for x in range(2*n)]
        rlas = [x>2*n for x in range(2*n)]
        
        def setPos(n: int, x: int, y: int) -> None:
            global rows, cols, llas, rlas
            # l, r = y-x, x+y
            l, r = n-1+y-x, x+y
            rows[x], cols[y], llas[l], rlas[r] = 1,1,1,1

        def rstPos(n: int, x: int, y: int) -> None:
            global rows, cols, llas, rlas
            # l, r = y-x, x+y
            l, r = n-1+y-x, x+y
            rows[x], cols[y], llas[l], rlas[r] = 0,0,0,0
            
        def getPos(n: int, x: int, y: int) -> bool:
            global rows, cols, llas, rlas
            # l, r = y-x, x+y 又大意了
            # llas是左斜的diagonal，rlas是右斜的diagonal
            # e.g. [0,0] 应该对应rows[0], cols[0], llas[0], rlas[3]
            # e.g. [0,3] 应该对应rows[0], cols[3], llas[3], rlas[6],即(n-1+y-x)
            l, r = n-1+y-x, x+y 
            return True if any([rows[x], cols[y], llas[l], rlas[r]]) else False
        
        def backtrack(n: int, level: int) -> int:
            global rows, cols, llas, rlas
            
            # 达到第n层表明存在一个可行解
            if (n == level): return 1
        
            rtn = 0
            for i in range(n):
                # 要检查[level][i]这个位置是否可以放置queen
                # if not getPos(n, level, i): 大意啦大意啦
                if getPos(n, level, i):
                    continue
                # push操作
                setPos(n, level, i)
                # 递归调用
                rtn += backtrack(n, level+1)
                
                # pop操作
                rstPos(n, level, i)
            return rtn
        
        return backtrack(n, 0)

    # 往上的另一种做法，没有看懂呢
    def totalNQueens(self, n: int) -> int:
        def dfs(queens, xy_dif, xy_sum):
            r = len(queens)
            if r==n:
                # 可以直接在dfs中访问totalNQueens里面的成员哟
                self.count += 1
                return 
            for c in range(n):
                if c in queens or r-c in xy_dif or r+c in xy_sum:
                    continue
                '''
                集合操作:
                交集  x & y
                并集  x | y
                差集  x - y 
                补集  x ^ y 注意 x^y和y^x的内容相同，但是顺序可能不一样
                '''
                dfs(queens + [c], xy_dif | {r-c}, xy_sum | {r+c}) 
        
        self.count = 0
        dfs([], set(), set())
        return self.count
        

if __name__ == "__main__":
  gua = Solution()
  # nums = [1,2,3]
  # rtn = gua.permute(nums)
  # print(rtn)
  rtn = gua.totalNQueens(4)
  print("expect result = 2, actual result = %d" % rtn)

  rtn = gua.totalNQueens(1)
  print("expect result = 1, actual result = %d" % rtn)

