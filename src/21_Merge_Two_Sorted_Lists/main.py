from typing import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
  # Runtime: 32 ms, faster than 91.75%
  # Memory Usage: 14.2 MB, less than 63.61%
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        # 两个链表的处理可以作为其他操作的基本block，例如merge sort两个list
        # 貌似递归函数的入参与主函数一致，所以互用主函数
        # 返回条件
        if not l1 or not l2:
            return l2 if l2 else l1

        # 现在l1和l2都合法了
        newHead = None
        if l1.val <= l2.val:
            l1Next = l1.next
            l1.next = self.mergeTwoLists(l1Next, l2)
            newHead = l1
        else:
            l2Next = l2.next
            l2.next = self.mergeTwoLists(l1, l2Next)
            newHead = l2
        return newHead
        # 因为递归放在最后，所以可以改写为recursive

def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()

  q4 = ListNode(4)
  q2 = ListNode(2,q4)
  q1 = ListNode(1,q2)

  p4 = ListNode(4)
  p3 = ListNode(3,p4)
  p1 = ListNode(1,p3)

  rtn = gua.mergeTwoLists(q1, p1)
  #print("expect value = 1, actual value = %d" % rtn)
  printNode(rtn)
  # print(v)

