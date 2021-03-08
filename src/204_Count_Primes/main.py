
class Solution:
    # n/2 + n/3 + n/5 + n/7...  时间复杂度O(N * loglogN)
    def countPrimes(self, n: int) -> int:
        # Sieve of Eratosthenes算法，每次扫描去掉存在multiple的那些值，[2,n)
        scans = [1 for x in range(0,n)]
        
        # Runtime: 4212 ms, faster than 8.60%
        # Memory Usage: 29 MB, less than 44.44%
        # for x in range(2,n): 可以优化一下
        x = 2
        while x*x <= n:
            # val = 2*x # 从两倍x开始
            val = x*x # 可以再优化一下，从x*x开始
            while val < n:
                scans[val] = 0
                val += x
            x += 1
        
        rtn = 0
        for x in range(2,n):
            rtn += (1 if scans[x] else 0)
            
        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.countPrimes(n = 10)
    print("expect result = 4, actual value = %d" % rtn )

    rtn = gua.countPrimes(n = 0)
    print("expect result = 0, actual value = %d" % rtn )

    rtn = gua.countPrimes(n = 1)
    print("expect result = 0, actual value = %d" % rtn )

