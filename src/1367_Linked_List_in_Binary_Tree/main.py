
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

dict = []

class Solution:
    # Runtime: 88 ms, faster than 94.00%
    # Memory Usage: 16.8 MB, less than 37.64%
    # 从先序遍历和后续遍历里面选择了前者，因为后者的话还要专门记录一些信息
    def isSubPath(self, head: ListNode, root: TreeNode) -> bool:
        # 返回条件 TODO
#         # 我觉得下面的方法只适用于path末端为叶子节点的情况
#         # 如果出现[1,4,1,null,null,4,2,6]的树和[1,4,2,6]的链表就搞不定了，用KMP试试
#         #此时若root为null，则空链在空树里，返回true；或者链表完全包含在树里面，也返回true
#         if not head: return True
#         #此时链表不为空，但是树为空，别想了，返回false
#         if not root: return False

#         # 判断是否需要移动linked list的pos，此时head和root都不为空了，安全
#         newHead = head->next if root.val == head.val else head

#         # 然后剩下的部分就是子问题了
#         lhs = isSubPath(root.left, newHead)
#         if lhs: return True

#         rhs = isSubPath(root.right, newHead)
#         return rhs
        # 需要O(m*m)的空间用于存储状态转移
        global dict
        dict = []
        #for val in range(0,101): dict.append([0]*101)

        # 构造dict有限状态机的前向跳转
        # pos = 0
        # while newHead:
        #     dict[pos][newHead.val] = pos+1
        #     pos++
        #     newHead = newHead.next
        pos, x = 1, 0
        # for i in range(1,pos):
        dict.append([0]*101)
        dict[0][head.val] = 1
        newHead = head.next
        while newHead:
            # 这里定义了后向跳转
            dict.append([0]*101)
            for val in range(1,101):
                # dict[pos][val] = x # 大意了，这里应该是状态转移！！
                dict[pos][val] = dict[x][val]
            # 这里定义了前向跳转，只会有一个值是可行的前向跳转
            dict[pos][newHead.val] = pos+1
            x = dict[x][newHead.val] #保留前向跳转的前一个状态
            pos += 1# pos++ 当成C++了
            newHead = newHead.next #控制while循环

        #现在开始遍历这棵树root
        def checkSubSeq(root: TreeNode, cur: int, last: int)->bool:
            global dict
            # 返回条件
            if not root: return False # 因为initial进入checkSubSeq时root不为null
            # 为null只可能在前一个节点不等于list值的情况下，那种情况下nxt != last，所以返回false

            nxt = dict[cur][root.val]
            if nxt == last: return True

            # 对左分支做同样处理
            rtn = checkSubSeq(root.left, nxt, last)
            if rtn: return True
            rtn = checkSubSeq(root.right, nxt, last)
            return rtn

        return checkSubSeq(root, 0, pos)

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

  m1 = TreeNode(1)
  m1a = TreeNode(1)
  m10 = TreeNode(10)
  m9 = TreeNode(9)
  m1.right = m1a; m1a.left = m10; m1a.right = m9

  q1 = ListNode(1)
  q10 = ListNode(10)
  q1.next = q10
  rtn = gua.isSubPath(q1, m1)
  print("expect value = 1, actual value = %d" % rtn)
  printNode(m1)

  n1 = TreeNode(1)
  n4_l = TreeNode(4)
  n4_r = TreeNode(4)
  n2_l = TreeNode(2)
  n2_r = TreeNode(2)
  n1_l = TreeNode(1)
  n6 = TreeNode(6)
  n8 = TreeNode(8)
  n3 = TreeNode(3)
  n1.left = n4_l; n1.right = n4_r
  n4_l.right = n2_l; n4_r.left = n2_r
  n2_l.left = n1_l; n2_r.left = n6
  n2_r.right = n8; n8.right = n3

  p4 = ListNode(4)
  p2 = ListNode(2)
  p8 = ListNode(8)
  p4.next = p2; p2.next = p8

  rtn = gua.isSubPath(p4, n1)
  print("expect value = 1, actual value = %d" % rtn)
  printNode(n1)


