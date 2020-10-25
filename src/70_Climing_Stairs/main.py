# coding=utf-8

class Solution(object):
    #Runtime: 20 ms, faster than 47.98% 
    #Memory Usage: 13.3 MB, less than 7.10% 
    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
        # 已经进行了空间压缩，p2和p1分别表示p[n-2],p[n-1]
        p2, p1 = 1, 1
        for i in range(1,n):
            #p[n] = p[n-2] + p[n-1]
            #tmp = p2 + p1
            #p2 = p1
            #p1 = tmp
            p2, p1 = p1, p2
            p1 = p1+p2
        return p1

if __name__ == "__main__":
  gua = Solution()
 
  rtn = gua.climbStairs(n=2)
  print("expect value = 2, actual value = %d" % (rtn))

  rtn = gua.climbStairs(n=3)
  print("expect value = 3, actual value = %d" % (rtn))

