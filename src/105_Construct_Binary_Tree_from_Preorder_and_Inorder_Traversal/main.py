from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    # Runtime: 340 ms, faster than 12.68%
    # Memory Usage: 19.6 MB, less than 57.11%
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        def buildSubTree(preorder: List[int], bgnP: int, endP: int, inorder: List[int], bgnI: int, endI: int) -> TreeNode:
            if bgnP >= endP or bgnI >= endI:
                return None
            
            # 左分支处理
            endILhs = endI
            for pos in range(bgnI, endI):
                if preorder[bgnP] == inorder[pos]:
                    endILhs = pos
                    break
            lenLhs = endILhs - bgnI # [0,1) -> len = 1
            
            endPLhs = bgnP + 1 + lenLhs # 0, len = 1 -> [1,2)
            nodeLhs = buildSubTree(preorder, bgnP + 1, endPLhs, inorder, bgnI, endILhs)
            
            # 右分支处理
            bgnPRhs = endPLhs
            nodeRhs = buildSubTree(preorder, bgnPRhs, endP, inorder, endILhs+1, endI)
            
            # 中间节点处理
            root = TreeNode(preorder[bgnP])
            root.left = nodeLhs
            root.right = nodeRhs
            return root
        
        # 就是要把这个问题化小变为子问题
        # pre-order数组的第一个值是root，然后由于没有duplicate，那么找到inorder里面的root之后
        # inorder里面左边所有的值都是左分支的（个数可以确定，为m），然后右边所有都是右分支的；
        # 然后inorder里面所有左分支的部分与pre-order里面所有左分支的值（root后面m个数）可以继续调用buildTree函数
        lenP, lenI = len(preorder), len(inorder)
        if lenP != lenI:
            return None
        
        rtn = buildSubTree(preorder, 0, lenP, inorder, 0, lenI)
        return rtn

def printNode(root: TreeNode):
  print("[",end="")

  st = [root]
  while len(st):
    size = len(st)
    level = ""
    isValid = False
    for i in range(size):
      cur = st[0]
      st.pop(0) # 总是从前面取

      if cur:
        isValid = True
        level+=(str(cur.val)+",")
        if cur.left or cur.right:
          st.append(cur.left)
          st.append(cur.right)
      else:
        level+="null,"

    if isValid:
      print(level, end="")

  print("]")

if __name__ == "__main__":
  gua = Solution()
  preorder = [3,9,20,15,7]
  inorder = [9,3,15,20,7]
  rtn = gua.buildTree(preorder, inorder)
  printNode(rtn)

