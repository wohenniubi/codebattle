from typing import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    # Runtime: 36 ms, faster than 19.69% 
    # Memory Usage: 14.8 MB, less than 5.23%
    def reverseBetween(self, head: ListNode, m: int, n: int) -> ListNode:
        # 感觉就是个树的递归问题，当遍历到2和3时，交换2，3，以3继续遍历
        # 然后继续遍历到3和4，交换3，4；因此要知道当前所处的位置是不是[m,n]的交换区间
        # 入参包括pos，当前节点，下一个节点
        # 采用先序遍历的模式，处理完剩余节点之后返回根节点，然后上层根节点指向返回的节点
        def reverseNodes(head: ListNode, tail:ListNode, m: int, n: int, pos: int) -> (ListNode, ListNode):
        #def reverseNodes(head: ListNode, tail:ListNode, m: int, n: int, pos: int):
            # 返回条件TODO，由于保证1 ≤ m ≤ n ≤ length of list，所以可以不用检查head是否为空
            if pos >= n: return head, tail
            
            # [m, n] 共分为3个区间[1,m), [m,n], [n,...)
            if pos < m:
                child = head.next
                childHead, childTail = reverseNodes(child, child, m, n, pos+1)
                head.next = childHead # 需要更新一下
                return head, childTail
            else:
                #[m,n)区间需要交换head和head.next，要保存head.next.next
                # 之前没有想清楚，现在来一把解决
                # 就是要让head, tail, tail.next 变成tail.next(1), tail(2), tail.next.next(3)三个任务
                tmp = tail.next
                tail.next = tmp.next # 完成任务3
                tmp.next = head # 完成任务1，part2/2
                head = tmp # 完成任务1，part1/2
                # tail保持不变，然后继续递归调用
                return reverseNodes(head, tail, m, n, pos+1) # 1,3,2,4,5
                
        # 由于1<=m<=n<=len，所以不会有空的情况，但是要注意几个corner cases
        # m = n = 1     len = 1
        # m = n = 2     len = 2
        # m = 1, n = 2  len = 2
        # m = 2, n = 2  len = 2
        # m = 2, n = 4  len = 5
        #head, _ = reverseNodes(head, head, m, n, 1)
        #return head
        return reverseNodes(head, head, m, n, 1)[0]

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
  rtn = gua.reverseBetween(q1, m=2, n=4)
  #print("expect value = 1, actual value = %d" % rtn)
  printNode(rtn)
  # print(v)


