
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        # 要不就先遍历一遍？
        def cntBothNode(root: TreeNode, p: TreeNode, q: TreeNode)->int:
            if not root: return 0
            # 该函数返回以root为根节点的树里面包含的p，q的个数，由于先计算子节点，所以应该算是后续遍历
            
            lhs = cntBothNode(root.left, p, q)
            rhs = cntBothNode(root.right, p, q)
            
            rtn = 1 if root == p or root == q else 0
            return rtn + lhs + rhs
        
        def getLowestCA(root: TreeNode, p: TreeNode, q: TreeNode)->TreeNode:
            if not root: return None
            
            # 只有在p和q同时存在于root里面时才可以这样操作；否则无法区分只包含p或者q的root和同时包含p和q的root
            if root == p or root == q: return root
            
            lhs = getLowestCA(root.left, p, q)
            rhs = getLowestCA(root.right, p, q)
            
            # 不能过早见到非None的返回值就返回，还要判断是否是公共节点
            if lhs and rhs:
                return root
            else:
                return lhs if lhs else rhs
        
        if cntBothNode(root, p, q) != 2: return None
        
        return getLowestCA(root, p, q)

def printNode(root: TreeNode):
  print("[",end="")

  st = [root]
  while len(st):
    size = len(st)
    level = ""
    isValid = False
    for i in range(size):
      cur = st[0]
      st.pop(0) # 总是从前面取; 默认不带参数的话等价于-1，从尾部取

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
  n3 = TreeNode(3)
  n5 = TreeNode(5)
  n1 = TreeNode(1)
  n6 = TreeNode(6)
  n2 = TreeNode(2)
  n0 = TreeNode(0)
  n8 = TreeNode(8)
  n7 = TreeNode(7)
  n4 = TreeNode(4)
  n3.left = n5; n3.right = n1
  n5.left = n6; n5.right = n2
  n1.left = n0; n1.right = n8
  n2.left = n7; n2.right = n4

  rtn = gua.lowestCommonAncestor(n3, n5, n1)
  printNode(rtn)

  rtn = gua.lowestCommonAncestor(n3, n5, n4)
  printNode(rtn)

  n9 = TreeNode(9)
  rtn = gua.lowestCommonAncestor(n3, n5, n9)
  printNode(rtn)

