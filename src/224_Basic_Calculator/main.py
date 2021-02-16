
class Solution:
    # Runtime: 136 ms, faster than 29.06% 
    # Memory Usage: 15.9 MB, less than 21.37%
    def calculate(self, s: str) -> int:
        # 先选择一个框架来做简化版的问题，再逐渐往这个框架上增加东西
        # 这里选择的是快慢索引+递归的框架，来试着做一下哇
        
        stack = []
        pos = 0
        def traverse(s: str, pos: int) -> (int, int):
            totalSum, localSum = 0, 0 # 后者用于累积识别的数字
            itemCnt = 0
            prevSign = '+'
            
            if pos == len(s):
                return totalSum, pos
            
            while pos < len(s):
                c = s[pos]
                if c.isdigit():
                    localSum = localSum*10 + int(c)
                
                # 现在处理()，这相当于是递归，递归返回之后相当于一个值
                if c == '(':
                    #localSum, pos = traverse(s, pos) 超级大意啊！！要从pos下一步开始
                    localSum, pos = traverse(s, pos+1)
                    # 这里并不需要返回，要继续执行下面的判断
                    # 如果有2(2-3)这样的关系，那么这里需要修改prevSign为*
                    
                # 这里为了在非digit的情况下触发操作，并且考虑最后一个字符，因此不能写成else
                # if not c.isdigit() and c != ' ' and pos == len(s)-1:
                if (not c.isdigit() and c != ' ') or pos == len(s)-1:
                    if prevSign == '+':
                        #totalSum += localSum
                        stack.append(localSum)
                        itemCnt += 1
                    elif prevSign == '-':
                        # totalSum -= localSum
                        stack.append(-localSum)
                        itemCnt += 1
                    elif prevSign == '*':
                        # 好吧，还是需要一个stack的
                        stack[-1] *= localSum
                    elif prevSign == '/':
                        stack[-1] = int(stack[-1]/localSum)
                    else:
                        pass # assert(0) 这里不需要增加assert
                    localSum, prevSign = 0, c
                
                if c == ')': break
                pos += 1
                # if c == ')': break 不应该在")"时往后移动pos，因为")"返回之后是在"("那里，
                # 后者会进入触发分支，触发分支结束后会让pos+1，这样会跳过后面的符号，导致错误
            
            # while循环结束之后叠加到totalSum里面
            while itemCnt:
                totalSum += stack.pop(-1)
                itemCnt -= 1
            return totalSum, pos # 等价于写作(totalSum, pos)

        return traverse(s, pos)[0]

if __name__ == "__main__":
  gua = Solution()
  rtn = gua.calculate(s = "(1+(4+5+2)-3)+(6+8)")
  print("expect result = 23, actual result = %d" % rtn)

  rtn = gua.calculate(s = "2-1 + 2")
  print("expect result = 3, actual result = %d" % rtn)

  rtn = gua.calculate(s = "1 + 1")
  print("expect result = 2, actual result = %d" % rtn)

