from typing import List

class NestedInteger:
    def __init__(self, listItem:[]) -> None:
        self.isVal = True if type(listItem) == int else False
        self.val = listItem if type(listItem) == int else None
        self.items = listItem if type(listItem) != int else []

    def addInteger(self, newItem):
        self.isVal = False
        self.items.append(newItem)

    def isInteger(self) -> bool:
        return self.isVal
        """
        @return True if this NestedInteger holds a single integer, rather than a nested list.
        """

    def getInteger(self) -> int:
        return self.val if self.isVal else None
        """
        @return the single integer that this NestedInteger holds, if it holds a single integer
        Return None if this NestedInteger holds a nested list
        """

    #def getList(self) -> [NestedInteger]:
    def getList(self):
        return self.items if not self.isVal else None
        """
        @return the nested list that this NestedInteger holds, if it holds a nested list
        Return None if this NestedInteger holds a single integer
        """

class NestedIterator:
    # Runtime: 84 ms, faster than 12.01% 
    # Memory Usage: 17.1 MB, less than 97.65%
    # 粗劣想了一下，本题就是个N叉树遍历，同时是逐次调用的，因此有点类似于生成器，故需要保留一些信息方便再次调用时继续执行
    # 再想了一下，返回的顺序有点像是中序遍历的顺序，所以算法采用中序遍历；
    # 保留指针的话必定是不方便的，所以仿照iterative遍历使用了一个容器来存储还没有处理完的NestedInteger
    def __init__(self, nestedList: [NestedInteger]):
        # self.st = []
        # st.append(nestedList) 大意啦大意啦
        # self.st.append(nestedList)
        # for item in nestedList: self.st.append(item)
        self.st = nestedList
    
    def next(self) -> int:
        item1 = self.st.pop(0)
        return item1.getInteger()
        
    # 这个函数的意义就是每次在询问时，会分解st里面的第一个item，然后不断添加到st里面去；为保证顺序，这里处理完[0]之后又放回头部
    def hasNext(self) -> bool:
        if not self.st:
            return False

        # 现在就是有效的st
        # while self.st and not self.st[0].isInteger():
        while self.st:
            # 进入之后必定第一个item不是integer，拆分它
            # item1 = self.st.pop(0)
            item1 = self.st[0]
            if type(item1) == NestedInteger:
                if item1.isInteger():
                  break
                else:
                  tmp = item1.getList()
            else:
                tmp = item1
            self.st.pop(0)
            # self.st = tmp.append(self.st) 大意了大意了，append没有返回值
            for item in self.st: tmp.append(item)
            self.st = tmp

        # 跳出while说明st为空或者第一个元素为integer；两者只需要返回st是否为空就好了
        # return len(self.st) == 0 大意啦大意啦
        return len(self.st) != 0

# Your NestedIterator object will be instantiated and called as such:
# i, v = NestedIterator(nestedList), []
# while i.hasNext(): v.append(i.next())

# def printNode(root: TreeNode):
#   print("[",end="")

#   st = [root]
#   while len(st):
#     size = len(st)
#     level = ""
#     isValid = False
#     for i in range(size):
#       cur = st[0]
#       st.pop(0) # 总是从前面取

#       if cur:
#         isValid = True
#         level+=(str(cur.val)+",")
#         if cur.left or cur.right:
#           st.append(cur.left)
#           st.append(cur.right)
#       else:
#         level+="null,"

#     if isValid:
#       print(level, end="")

#   print("]")

if __name__ == "__main__":
  n1 = NestedInteger(1)
  n2 = NestedInteger(2)
  # n3 = NestedInteger([1,1])
  input = [[n1]*2,n2,[n1]*2]

  gua, v = NestedIterator(input), []
  while gua.hasNext(): v.append(gua.next())
  # rtn = gua.buildTree(preorder, inorder)
  # printNode(rtn)
  print(v)


