
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    #Runtime: 72 ms, faster than 67.30%
    #Memory Usage: 25.4 MB, less than 48.18% 
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        # 按照binary tree的操作模版，把任务划分为几个小部分
        # 觉得应该用先序遍历处理，这里的先序要对p和q进行判断，具体写法在其他题见识过
        # (1) if root == p: 对左右分支查找q
        # (2) if root == q: 对左右分支查找p
        # (3) 在(1)(2)之后root与p，q皆不相等，问题又变回了初始状态：先对左分支递归，如果返回为真，则结束；否则对右分支递归

        # 然后如果不想另外写一个新的递归函数来查找一个node，那么就复用这个函数lowestCommonAncestor，比如：
        # 把p和q设置为一样，再判断root是否同时等于两个节点，这样是不是很fancy，哦耶！
        # TODO: 返回条件root为None
        if not root: return None

        # 中间节点的处理，关键是要处理两种任务：p，q分配在左右两个分支的情况；p，q是对方的parent
        if root == p or root == q:
            return root
        # 以下操作解决不了p，q分配在左右两个分支的情况
        # if root == p:
        #     if root == q: return root
        #     lca = lowestCommonAncestor(root.left, q, q)
        #     if lca: return
        # if root == q:
        #     pass

        # 此时root与左右都不等，那么继续吧
        lhs = self.lowestCommonAncestor(root.left, p, q)
        # if lca: return lca 直接返回并不好，因为无法区分不为None的这个值是某个要查找的p或者q，还是lca

        rhs = self.lowestCommonAncestor(root.right, p, q)
        # return lca # 好像错过了p，q分配在左右两个分支的情况
        # if lca: return lca 直接返回并不好，因为无法区分不为None的这个值是某个要查找的p或者q，还是lca

        if not lhs or not rhs:
            # 只要有一方为None，就选择另一方
            return lhs if lhs else rhs
        else:
            # 只可能是p和q分配在root的左右分支的情况，那么这个root就符合lca的条件
            return root

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

