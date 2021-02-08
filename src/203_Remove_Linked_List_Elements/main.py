
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeElements(self, head: ListNode, val: int) -> ListNode:
        '''
        看到链表先想到树，然后就是递归，然后考虑转换为iterasive
        迭代的做法就是要确保while循环，例如：cur.next是否存在，或者cur是否存在，
        然后在处理cur之前，先把cur的链表关系保持好（把cur保存到tmp，然后从链表中摘除tmp），
        再循环处理—— 由于要使用cur.next，因此要先判断cur是否有效
        '''
        #if not head: return head
        
        cur = head
        # prev = ListNode(666, head) 应该称之为dummy node
        dummy = ListNode(666, head)
        prev = dummy
        while cur:
            if cur.val == val:
                tmp = cur
                prev.next = cur.next #原本prev.next是cur，现在往后跳一个，但是prev还是不动
                
                # 那么更新cur为cur.next，去掉tmp，然后让cur继续执行
                cur = cur.next
                # 等等还要维护前一个node的next
                del tmp
            else:
                # prev.next = cur 不删除的话，prev.next已经指向cur，不劳烦更新
                prev = cur # 不过此时prev要更新为cur呀！！！！
                # 不等于的话很安全，直接更新cur为cur.next
                cur = cur.next
        
        # head = prev.next 这里错了！！！！！prev已经到后面了，尼玛应该用dummy node！！
        head = dummy.next
        del dummy #del prev
        return head # head携带了新的链表信息，或者head本身就是空的
            

def printNode(root: ListNode):
  print("[", end="")
  while root:
    print("%d," % root.val, end="")
    root = root.next
  print("]")

if __name__ == "__main__":
  gua = Solution()
  p6 = ListNode(6)
  p5 = ListNode(5, p6)
  p4 = ListNode(4, p5)
  p3 = ListNode(3, p4)
  p6 = ListNode(6, p3)
  p2 = ListNode(2, p6)
  p1 = ListNode(1, p2)

  printNode(p1)
  rtn = gua.removeElements(p1, 6)
  printNode(rtn)

