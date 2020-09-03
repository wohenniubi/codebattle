# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution(object):
    def helper(self, root, val):
        if not root:
            return None
        
        if root.val == val:
            return root
        
        if val < root.val: 
          return self.helper(root.left, val)
        else:
          return self.helper(root.right, val)
    
    def searchBST(self, root, val):
        """
        :type root: TreeNode
        :type val: int
        :rtype: TreeNode
        """
        return self.helper(root, val)

if __name__ == "__main__":
  gua = Solution()
  
  n4 = TreeNode(4)
  n7 = TreeNode(7)
  n2 = TreeNode(2)
  n4.left = n2; n4.right = n7
  n1 = TreeNode(1)
  n3 = TreeNode(3)
  n2.left = n1; n2.right = n3

  rtn = gua.searchBST(n2, 2)

  print("[%d,%d,%d]" % (rtn.val, rtn.left.val, rtn.right.val))
