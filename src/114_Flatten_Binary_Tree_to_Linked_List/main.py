
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 别人写的代码，基本思路一致，不过要简洁很多，学习了
class Solution:
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        def helper(node):
            # helper always returns the 'tail' or 'leaf' node in left/right
            if not node:
                return
            # 这里提前对叶子节点进行判断，可以简化后面的处理
            if not node.left and not node.right:
                return node
            
            lh = helper(node.left)
            rh = helper(node.right)
            
            if lh:
                lh.right = node.right
                node.right = node.left
                node.left = None
            
            return rh if rh else lh
        
        helper(root)

class Solution1:
    # Runtime: 32 ms, faster than 91.80% 
    # Memory Usage: 15.3 MB, less than 31.52%
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        # 思考一下每个节点的任务应该如何分配
        # 如果能在每个节点的操作结束之后返回指向链表最后的pointer，然后就妥了
        def flattenToRight(root: TreeNode) -> TreeNode:
            if not root:
                return root

            # 右分支操作
            rhs = root.right
            rEnd = flattenToRight(rhs)# 真是大意啦大意啦 self.flatten(rhs) 

            # 左分支操作
            lhs = root.left
            if lhs:
                lEnd = flattenToRight(lhs)# 真是大意啦大意啦 self.flatten(lhs)
                root.left = None
                root.right = lhs
                if lEnd:
                    lEnd.right = rhs# rEnd
                rEnd = lEnd if not rEnd else rEnd

            # 中间节点操作
            rEnd = root if not rEnd else rEnd
            return rEnd
        
        flattenToRight(root)

def printNode(root: TreeNode):
  cur = root
  #python2.X的话直接加,就可以了
  print("[", end="")
  while cur:
    print("%d," % cur.val, end="")
    print("null," if not cur.left else "Error", end="")
    cur = cur.right
  print("]")

if __name__ == "__main__":
  gua = Solution()
  n1 = TreeNode(1)
  n2 = TreeNode(2)
  n3 = TreeNode(3)
  n4 = TreeNode(4)
  n5 = TreeNode(5)
  n6 = TreeNode(6)

  n1.left = n2; n1.right = n5
  n2.left = n3; n2.right = n4
  n5.right = n6

  gua.flatten(n1)
  printNode(n1)

