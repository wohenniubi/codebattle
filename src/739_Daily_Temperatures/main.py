from typing import List

class Solution:
    # 也可以从左往右遍历，那样就需要在pop数据时更新stack里面的信息
    def dailyTemperatures(self, T: List[int]) -> List[int]:
        stack=[]
        # 不能直接用ans = range(len(T)), 这样貌似ans不是list, 而是个generator
        ans=[0 for _ in range(len(T))]
        for i in range(len(T)):
            while stack and T[stack[-1]]<T[i]:
                ans[stack[-1]]=i-stack[-1]
                stack.pop()
            stack.append(i)
        return ans

    #Runtime: 524 ms, faster than 45.99%
    #Memory Usage: 18.5 MB, less than 81.84%
    def dailyTemperatures1(self, T: List[int]) -> List[int]:
        # 这次一眼就看出来该怎么做，感谢
        # s = []; rtn = range(0, len(T))
        s = []; rtn = [x for x in range(0, len(T))]
        for i in range(0,len(T)):
            # i取值[0,n-1]，-i-1就是倒序[-1,-2,-3,-(n-1)]
            # pos = -i-1
            pos = len(T)-i-1
            while s and T[pos] >= T[s[-1]]:
                # 这里稍微有点变化，s存的应该是index，因为要计算相差的天数
                s.pop(-1)
            # 跳出while说明s为空或者s中（T[-i-1] 的右边）出现了较大值
            # rtn[pos] = 0 if not s else s[-1] - pos + 1
            rtn[pos] = 0 if not s else s[-1] - pos # 语义上的“隔一天”不是len，而是pos相减
            s.append(pos)
        return rtn

if __name__ == "__main__":
  gua = Solution()
  rtn = []

  T = [73, 74, 75, 71, 69, 72, 76, 73]
  exp = [1, 1, 4, 2, 1, 1, 0, 0]
  rtn = gua.dailyTemperatures(T)
  print("expect result = ", end=""); print(exp)
  print("actual result = ", end=""); print(rtn)


