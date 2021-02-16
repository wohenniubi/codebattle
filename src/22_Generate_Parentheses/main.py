from typing import List

class Solution:
    #Runtime: 32 ms, faster than 86.35%
    #Memory Usage: 14.7 MB, less than 40.79%
    def generateParenthesis(self, n: int) -> List[str]:
        # 采用回溯方法，确定path，选择(及限制)还有base条件(及定义)，必要时加入memo进行去除重复计算
        
        # memo = {} # 去除重复计算
        
        rtn = []
        # 这个函数的输入是路径和剩余的(和)个数，先暴力试试会不会通过
        def traverse(path: str, lcnt: int, rcnt: int):
            if lcnt == 0:
                tmp = path + ")"*rcnt
                rtn.append(tmp)
                return
            
            # 现在lcnt不为0
            if lcnt == rcnt:
                # 这种情况下只能选(
                traverse(path + '(', lcnt-1, rcnt)
            else:
                assert(lcnt < rcnt) #否则会出现不合法结果
                # 这种情况下可以选(也可以选)
                for i in range(2):
                    if i == 0:
                        path = path + "("
                        tmp = traverse(path, lcnt-1, rcnt)
                    else:
                        path = path + ")"
                        tmp = traverse(path, lcnt, rcnt-1)
                    path = path[:-1]
            return
        
        traverse("", n, n)
        return rtn

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.generateParenthesis(1)
  print(rtn)

  rtn = gua.generateParenthesis(3)
  print(rtn)

