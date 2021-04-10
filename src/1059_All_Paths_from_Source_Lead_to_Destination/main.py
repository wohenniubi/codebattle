
from typing import List

class Solution:
    # Runtime: 296 ms, faster than 25.55%
    # Memory Usage: 19.8 MB, less than 43.67%
    def leadsToDestination(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        # 觉得貌似就是DFS遍历，过程中如果出现loop就返回false，如果叶子结点不是destination也返回false
        # 由于是图，所以需要一个memo，记录node的访问信息；然后输入是edges，所以还要先构建图
        def dfs(source, destination):
            # 返回条件
            if source not in graph:
                # 说明是叶子结点
                return source == destination
            
            # 当前节点是否被访问
            if memo[source] != 0:
                return memo[source] == 1 # -1表示有环
            else:
                memo[source] = -1 # 灰色表示正在被访问
            
            # 遍历当前节点的所有邻居
            for adj in graph[source]:
                # 因为是有向图，所以不需要担心来时的路
                if not dfs(adj, destination):
                    return False

            # 跳出for循环时，每个邻居都OK，那么当前节点处理结束
            memo[source] = 1
            return True
            
        memo = [0] * n # 0表示还没有访问
        graph = {}
        
        for edge in edges:
            src, end = edge
            if src in graph:
                graph[src].append(end)
            else:
                graph[src] = [end]
        return dfs(source, destination)

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.leadsToDestination(n=3, edges=[[0,1],[0,2]], source=0, destination=2)
  print("expect value = False, actual value = ", rtn)

  rtn = gua.leadsToDestination(n=4, edges=[[0,1],[0,3],[1,2],[2,1]], source=0, destination=3)
  print("expect value = False, actual value = ", rtn)

  rtn = gua.leadsToDestination(n=4, edges=[[0,1],[0,2],[1,3],[2,3]], source=0, destination=3)
  print("expect value = True, actual value = ", rtn)

  rtn = gua.leadsToDestination(n=3, edges=[[0,1],[1,1],[1,2]], source=0, destination=2)
  print("expect value = False, actual value = ", rtn)

  rtn = gua.leadsToDestination(n=2, edges=[[0,1],[1,1]], source=0, destination=1)
  print("expect value = False, actual value = ", rtn) 

