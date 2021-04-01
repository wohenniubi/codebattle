# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    #Runtime: 48 ms, faster than 73.08%
    #Memory Usage: 16.2 MB, less than 76.89%
    def rob(self, root: TreeNode) -> int:
        # 乍一眼就觉得是dp问题，两个状态，其中一个是节点，另一个是包含head或者不包含head的最大值
        def dp(root: TreeNode)->(int, int):
            # 返回条件
            if not root: # 剩下的就交给递归吧，我累了
                return 0,0

            lhs = dp(root.left)
            rhs = dp(root.right)

            # 现在是看选择了，如果选择root，那么左右两个分支只能使用不包含root的值
            # 如果不选择root，那么就选择左右两个分支里面的最大值再求和
            withRoot = root.val + lhs[1] + rhs[1]
            woRoot = max(lhs) + max(rhs)
            return withRoot, woRoot

        return max(dp(root))

if __name__ == "__main__":
    gua = Solution()
    q3 = TreeNode(3)
    q1 = TreeNode(1)
    q2 = TreeNode(2,None,q3)
    qt = TreeNode(3,None,q1)
    root = TreeNode(3, q2, qt)
    rtn = gua.rob(root)
    print("expect value = 7, actual value = %d" % rtn)

    p3 = TreeNode(3)
    p1 = TreeNode(1)
    p4 = TreeNode(4,p3,p1)
    po = TreeNode(1)
    p5 = TreeNode(5,None,po)
    root = TreeNode(3, p4, p5)
    rtn = gua.rob(root)
    print("expect value = 9, actual value = %d" % rtn)

