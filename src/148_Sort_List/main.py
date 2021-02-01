
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    # Runtime: 436 ms, faster than 76.99%
    # Memory Usage: 30.1 MB, less than 89.85%
    def sortList(self, head: ListNode) -> ListNode:
        # 首先找到链表中点，然后分别对两部分进行分治处理，基本是先序遍历
        #def findMidNode(head: ListNode, tail: ListNode) -> ListNode:
        def findMidNode(head: ListNode) -> ListNode:
            # 使用快慢指针找到中点
            prev, slow, fast = None, head, head
            # while slow and fast: and slow != tail and fast != tail
            while slow and fast:
                prev = slow
                slow, fast = slow.next, fast.next
                if not fast: break
                fast = fast.next
            # 跳出循环说明到头了，此时slow就是中点靠右的那个值
            if prev: prev.next = None #打断链表，免得后续出问题
            return slow

        def mergeSort(head: ListNode) -> ListNode:
            if not head or not head.next: return head

            midNode = findMidNode(head) #, tail: ListNode
            lhsHead = mergeSort(head) # , midNode
            rhsHead = mergeSort(midNode) #, tail

            # 将左右两个sorted分支进行合并，这次写成iterative形式
            newHead, prev = None, None
            while lhsHead and rhsHead:
                if lhsHead.val <= rhsHead.val:
                    # 将lhsHead作为新的头
                    if not newHead:
                        newHead, prev = lhsHead, lhsHead
                    else:
                        prev.next = lhsHead
                        prev = prev.next
                    lhsHead = lhsHead.next
                else:
                    if not newHead:
                        newHead, prev = rhsHead, rhsHead
                    else:
                        prev.next = rhsHead
                        prev = prev.next
                    rhsHead = rhsHead.next
            # 跳出循环时，必定有一方链表为空
            prev.next = rhsHead if not lhsHead else lhsHead
            return newHead

        return mergeSort(head)
 
def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()

  q3 = ListNode(3)
  q1 = ListNode(1,q3)
  q2 = ListNode(2,q1)
  q4 = ListNode(4,q2)

  p0 = ListNode(0)
  p4 = ListNode(4,p0)
  p3 = ListNode(3,p4)
  p5 = ListNode(5,p3)
  p1 = ListNode(-1,p5)

  rtn = gua.sortList(q4)
  #print("expect value = 1, actual value = %d" % rtn)
  printNode(rtn)

  rtn = gua.sortList(p1)
  #print("expect value = 1, actual value = %d" % rtn)
  printNode(rtn)

