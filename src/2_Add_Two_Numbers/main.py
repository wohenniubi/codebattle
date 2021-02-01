from typing import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addNNumbers(self, lists: List[ListNode], carry: int) -> ListNode:
        if not any(lists):
            val, carry = carry%10, int(carry/10)
            if carry:
                # 也可以专门写一个函数来创建链表以减少对addNNumbers的调用
                newNode = ListNode(val)
                newNode.next = self.addNNumbers(lists, carry)
                return newNode
            else:
                return ListNode(val) if val else None

        rtn, sum2 = None, carry
        for l in lists:
            if not rtn and l: rtn = l # 初始化rtn为第一个不为空的值
            sum2 = sum2 + (0 if not l else l.val)
        rtn.val = sum2%10 # 如果有超过10个list相加怎么办
        sum2 = sum2 - rtn.val
        newLists = [(l if not l else l.next) for l in lists]
        rtn.next = self.addNNumbers(newLists, sum2)
        return rtn

    # Runtime: 76 ms, faster than 25.90%
    # Memory Usage: 14.6 MB, less than 12.23%
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        # 感觉这就是merge两个linked list的操作，当成两颗树呗，先序遍历
        # 注意3点：1)要把子节点的返回值update一下；2)要一直运算到两个list都为空的情况
        # 3)要注意进位的操作，所以还要增加一个入参，所以不能直接复用addTwoNumbers了

        def addTwoLists(l1: ListNode, l2: ListNode, carry: int) -> ListNode:
            # 返回条件，要直到两个list都为空才行，也可以使用
            #if not l1 and not l2:
            if not any([l1,l2]):
                return ListNode(1) if carry else None

            # 这个框架可以改进为addNNumbers
            rtn, sum2 = None, carry
            for l in [l1, l2]:
                if not rtn and l: rtn = l # 初始化rtn为第一个不为空的值
                sum2 = sum2 + (0 if not l else l.val)
            rtn.val = sum2%10 # 如果有超过10个list相加怎么办
            sum2 = int(sum2/10) # 大意了！！！- rtn.val
            rtn.next = addTwoLists(l1 if not l1 else l1.next, l2 if not l2 else l2.next, sum2)
            return rtn
        return addTwoLists(l1, l2, 0) # 大意了，都忘记调用了

def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()

  q3 = ListNode(3)
  q4 = ListNode(4,q3)
  q2 = ListNode(2,q4)

  p4 = ListNode(4)
  p6 = ListNode(6,p4)
  p5 = ListNode(5,p6)

  rtn = gua.addTwoNumbers(q2, p5)
  #print("expect value = 1, actual value = %d" % rtn)
  printNode(rtn)

