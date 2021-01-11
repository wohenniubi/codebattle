# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

class Solution:
    # connect1的方式并不是最优的，因为过程中很多重复计算，不过幸好总节点数不多余4096，要不然妥妥的超时
    # 下面的方式借助了next节点，这样入参仅仅需要一个，其他操作由内卷完成;
    # Runtime: 64 ms, faster than 51.41% 
    # Memory Usage: 15.7 MB, less than 47.22%
    def connect(self, root: 'Node') -> 'Node':
        def connectLevel(root: 'Node') -> None:
            cur = root
            prev, sub = None, None
            
            # 这个while从左到右解决当前level所有节点的链接，可以理解为层后序遍历
            while cur:
                # 当前节点的左分支操作
                if prev:
                    prev.next = cur.left
                if not sub:
                    # 首选左分支，不行再选右分支，这样可以应对不是perfect binary的情况
                    sub = cur.left if cur.left else cur.right
                
                # 当前节点的右分支操作
                if cur.left:
                    cur.left.next = cur.right
                # 首选右分支，不行再选左分支，这样可以应对不是perfect binary的情况
                prev = cur.right if cur.right else cur.left
                
                # 当前节点的中间操作：平移到下一个节点
                cur = cur.next
            
            # 跳出while之后解决下一level的处理
            # 观察到这个递归调用在最后，因此可以进一步优化为iterative
            if sub:
                connectLevel(sub)
            return
            
        connectLevel(root)
        return root

    # Runtime: 236 ms, faster than 5.15% 
    # Memory Usage: 15.5 MB, less than 71.36%
    def connect1(self, root: 'Node') -> 'Node':
        #def connectTwoNode(node1: 'Node', node2: 'Node') -> None:
        def connectTwoNode(node1: 'Node', node2: 'Node') -> 'None':
            if not node1 or not node2:
                return

            node1.next = node2
            connectTwoNode(node1.left, node1.right)
            connectTwoNode(node2.left, node2.right)

            connectTwoNode(node1.right, node2.left)
            return
        
        # 尼玛不是说好了每个节点都有两个子节点吗？所以没有为root增加None判断
        if root:
            connectTwoNode(root.left, root.right)
        return root

if __name__ == "__main__":
  gua = Solution()
  
  n1 = Node(1)
  n2 = Node(2)
  n3 = Node(3)
  n1.left = n2; n1.right = n3
  n4 = Node(4)
  n5 = Node(5)
  n2.left = n4; n2.right = n5
  n6 = Node(6)
  n7 = Node(7)
  n3.left = n6; n3.right = n7

  rtn = gua.connect(n1)
  print("[%d,%d,%d]" % (rtn.val, rtn.left.val, rtn.right.val))

