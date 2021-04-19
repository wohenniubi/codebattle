
class Solution:
    # Runtime: 172 ms, faster than 18.46%
    # Memory Usage: 14.2 MB, less than 82.17%
    def multiply(self, num1: str, num2: str) -> str:
        # 尼玛，为了应对“0”的情况，要不然返回可能是"000"
        if num1 == "0" or num2 == "0":
            return "0"
        
        # 就是两个str相互遍历，但是关键是怎么实现迭代操作
        size1, size2 = len(num1), len(num2)
        
        # 因为仅仅是两个数相乘，所以最后的长度不超过size1 + size2 + 1
        vals = [] 
        for i in range(size1):
            cin = 0 # 从低位开始的进位
            for j in range(size2):
                # 此刻计算相乘之后，添加到vals中的某个位置
                pos = i+j
                if pos >= len(vals):
                    vals.append(0)
                
                # 因为还要考虑上一级的计算结果，所以要叠加vals[pos]
                # 这里也大意了，num1[0]和num2[0]都是最高位，应该选用最低位
                # vals[pos] += (ord(num1[i])-ord('0')) * (ord(num2[j])-ord('0')) + cin
                ti, tj = size1-1-i, size2-1-j
                vals[pos] += (ord(num1[ti])-ord('0')) * (ord(num2[tj])-ord('0')) + cin
                
                cin = vals[pos]//10
                vals[pos] = vals[pos] % 10
        
        # 大意了啊，是要在内部for loop后面，即每一位与另一个str完成乘法之后，要回收cin
            # 最后这个进位是不是要考虑到vals的最后呀
            if cin:
                vals.append(cin)
        
        # 好了，需要把rtn转换为str，且注意rtn[0]是最低位，题目要求[0]是最高位
        rtn, size = "", len(vals)
        for i in range(size):
            # 0 对应 size-1
            # 1 对应 size-2
            # size-1 对应 0
            rtn += chr(vals[size-1-i] + ord('0'))
            
        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.multiply(num1="9133", num2="0")
    print("expect result = 0, actual result = ", rtn)

    rtn = gua.multiply(num1="123", num2="456")
    print("expect result = 56088, actual result = ", rtn)

    rtn = gua.multiply(num1="2", num2="3")
    print("expect result = 6, actual result = ", rtn)


