
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    # Runtime: 32 ms, faster than 87.85%
    # Memory Usage: 20.4 MB, less than 6.65%
    def reverseList(self, head: ListNode) -> ListNode:
        # 当作一棵树来解决，然后回想三个问题：定义，状态，转换
        
        # 主要是根据“转换”->“状态”这里，预测到子问题需要返回两个值才能解决问题
        # 返回的tuple中包含新的链表头，以及链表尾
        def reverseTree(head: ListNode) -> (ListNode, ListNode):
            if not head or not head.next:
                return (head, head)
            
            # 好啦，现在head有效且至少有一个next
            # 让head.next作为子问题来解决，然后让返回值与head进行合并
            newHead, tail = reverseTree(head.next)
            head.next = None
            tail.next = head
            return newHead, head # 等价于(newHead, head)
        
        # 别忘了调用
        return reverseTree(head)[0]
    
    # 来哇，迭代做法，晚上脑子里面想的，空间复杂度O(1)，不需要使用list
    # Runtime: 36 ms, faster than 67.86%
    # Memory Usage: 15.7 MB, less than 49.60%
    def reverseList1(self, head: ListNode) -> ListNode:
        if not head: return None
        
        # 基本思路源自于递归做法，就是用当前block与剩下的节点进行处理
        # 每次将当前的block与其后面的一个ListNode一起组成一个不断增大的block
        # 这里为了保证block能够与下一个ListNode顺利合并，需要知道当前block的头和尾
        # 当前block的头和尾初始化为head和head
        newHead, tail = head, head
        while tail.next:
            tmp = tail.next # 先保存一下即将成为newHead的节点
            tail.next = tmp.next # 不能打断这个关联，要不然不能继续执行
            tmp.next = newHead
            newHead = tmp
        
        return newHead

def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()

  q5 = ListNode(5)
  q4 = ListNode(4,q5)
  q3 = ListNode(3,q4)
  q2 = ListNode(2,q3)
  q1 = ListNode(1,q2)

  print("before reverse = ", end=""); printNode(q1)
  rtn = gua.reverseList1(q1)
  print("after reverse  = ", end=""); printNode(rtn)


