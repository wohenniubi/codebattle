from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    pos = 0
    # 原本打算硬算的，就是遍历到最大值，然后分两段，再分别对两段进行递归，但是复杂度是O(n*logn)
    # 不过观察到两个关键点，1，root是最大值，2，新加入的点总是再右手边，于是感觉可以O(n)解决
    # Runtime: 204 ms, faster than 66.45%
    # Memory Usage: 15 MB, less than 27.47%
    def appendToTree(self, root: TreeNode, nums: List[int]) -> TreeNode:
        # 返回条件
        if self.pos >= len(nums):
            return root
        elif not root:
            root = TreeNode(nums[self.pos])
            self.pos = self.pos+1
            #return appendToTree(root, nums) 不能就这么返回，继续做操作
            return root
            # if self.pos >= len(nums)-1:
            #     return root
            
        # 现在root和pos都有效，与root进行判断，因为题目说val是unique的，所以很开心
        #root.right = appendToTree(root.right, pos, nums)
        if root.val < nums[self.pos]:
            # 先处理简单情况
            newRoot = TreeNode(nums[self.pos])
            self.pos = self.pos+1
            #newRoot.left = root 先不要武断的添加，交由上层appendToTree进行处理
            return newRoot
            
        # 由于可能出现后加的val大的情况，所以还不能武断的加入root.right
        tmp = self.appendToTree(root.right, nums)
        if root.val > tmp.val:
            if not root.right:
                root.right = tmp
            elif root.right != tmp:
                # 说明tmp比root的右分支大
                # 那么tmp的左分支继承原本的右分支
                tmp.left = root.right #tmp.right = root.right
                # 再把原本的右分支替换为tmp
                root.right = tmp

            # root.right = tmp if not root.right else root.right
            # 仅仅在root的右分支与新节点不同时，更新root,小于则不做处理
            # if root.right != tmp:
            #     tmp.right = root.right
            #     root.right = tmp
            # return root # 直接返回root可能还没有算完
            return self.appendToTree(root, nums)
        else:
            return tmp
        # if root.val > nums[pos]:
        #     # 比root小，并且比root的顺序靠后
        # else:
        #     # 比root大，那么需要进行节点交换
        #     tmp = TreeNode(nums[pos])
        #     tmp.left = root
        #     return tmp
    def constructMaximumBinaryTree(self, nums: List[int]) -> TreeNode:
        self.pos = 0 # python貌似没有reference，那么就用全局变量吧
        dummy = TreeNode(1001) #比所有节点都大；如果不告知这个nums的范围的话，那么就只能传入None，由函数内部自己判断
        root = self.appendToTree(dummy, nums)
        return dummy.right

def printNode(root: TreeNode):
  print("[",end="")

  st = [root]
  while len(st):
    size = len(st)
    level = ""
    isValid = False
    for i in range(size):
      cur = st[0]
      st.pop(0) # 总是从前面取; 默认不带参数的话等价于-1，从尾部取

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
  nums = [3,2,1,6,0,5]
  rtn = gua.constructMaximumBinaryTree(nums)
  printNode(rtn)

  nums = [3,1,2]
  rtn = gua.constructMaximumBinaryTree(nums)
  printNode(rtn)

  nums = [3,2,1]
  rtn = gua.constructMaximumBinaryTree(nums)
  printNode(rtn)


