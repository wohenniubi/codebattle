
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    #Runtime: 40 ms, faster than 82.24%
    #Memory Usage: 14.5 MB, less than 29.81% 
    def recDelNodes(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head

        # 现在head非空且存在至少两个node
        child = head.next
        if head.val == child.val:
            # 现在开始摘除head.next
            # head.next = self.recDelNodes(child.next) 大意了大意了！！应该还是从head开始
            head.next = child.next
            del child
            return self.recDelNodes(head)
        else:
            head.next = self.recDelNodes(child)
            return head

    def deleteDuplicates(self, head: ListNode) -> ListNode:
        '''
        已经是重复多次的题目，不过提供了一种思路，若要去掉链表或者array中的重复
        先进行排序，让重复的字符彼此粘连，然后再—使用快慢指针，遍历一遍去掉重复
        使用递归安全点
        '''
        return self.recDelNodes(head)

def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()

  q1 = ListNode(1)
  q1 = ListNode(1, q1)
  q1 = ListNode(1, q1)
  printNode(q1)
  q1 = gua.deleteDuplicates(q1)
  printNode(q1)



