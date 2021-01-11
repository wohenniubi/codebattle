
# Definition for singly-linked list.
class ListNode:
    # http://c.biancheng.net/view/2291.html 
    # 以下操作限制ListNode实例只能动态添加val和next成员或者val()和next()的方法
    __slots__ = ('val','next')
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    # Runtime: 44 ms, faster than 91.39% 
    # Memory Usage: 15.2 MB, less than 37.43% 
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        def reverseRange(head: ListNode, tail: ListNode) -> ListNode:
            # 遍历链表一般需要pre,cur，而翻转链表则需要使用三指针，pre，cur和nxt
            pre, cur = None, head
            # [1,2,3]
            while cur != tail:
              nxt = cur.next # 因为cur.next更新为pre，为了保证循环继续，故把next先保存下来
              cur.next = pre
              pre = cur #右移pre为当前node，当前node右移为下一个node
              cur = nxt
            return pre #while跳出时cur == tail，pre是tail左边的那个node，是新的head

        nxt = head
        # 想了半天，还是得先遍历到目标节点，反正时间复杂度都是O(n)，近似认为是post-order遍历
        # [1,2,3], k = 2, nxt->1, cnt=0, nxt->2; cnt=1, nxt->3; cnt=2 stop 
        # isReverse = True
        for cnt in range(k):
          if not nxt:
            # isReverse = False
            return head #这里直接返回head岂不是很香
          else:
            nxt = nxt.next
        # 分配每个“节点”的任务，这里的一个“节点”对应ListNode里面的k个节点，一个group
        # 左分支处理：翻转[head,nxt)之间的node，完了之后再处理右侧剩下的节点
        newHead = reverseRange(head, nxt) #head if not isReverse else reverseRange(head, nxt)
        # 由于已经有了head，nxt，那么只需要让reverse返回新的head就好了
        
        # 右分支处理：对剩余部分继续调用reverseKGroup
        kidHead = self.reverseKGroup(nxt, k)

        # 中间节点处理：将最后的结果进行重组
        head.next = kidHead # 大意了，写成head.nxt = kidHead了...
        # head.nxt = kidHead 由于加入了__slots__ = ('val','next')，这样会让head.nxt报错
        return newHead

def printNode(root: ListNode):
  cur = root
  print("[",end="")
  while cur:
    print("%d," % cur.val, end="")
    cur = cur.next
  print("]")

if __name__ == "__main__":
  gua = Solution()
  n1 = ListNode(1)
  n2 = ListNode(2)
  n3 = ListNode(3)
  n4 = ListNode(4)
  n5 = ListNode(5)
  n1.next = n2; n2.next = n3
  n3.next = n4; n4.next = n5

  rtn = gua.reverseKGroup(n1, 2)
  printNode(rtn)


