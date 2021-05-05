
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 73.20%
    //Memory Usage: 9.5 MB, less than 39.67%
    //改进：使用静态变量存uglys还有i2,i3,i5，这样它们的值不会随着nthUglyNumber结束而消失
    //这样如果nthUglyNumber需要多次调用，可以避免重复计算
    int nthUglyNumber(int n) {
        // 基本思路差不多，满足条件的n=(2^i)*(3^j)*(5^k)
        // 那么就让i,j,k都从0开始，每次增大i或者j或者k；
        // 同时还要维护一个数组，表明第n-1次的ugly number，则第n次的丑数会由之前的丑数产生
        // 由于第n次的丑数一定比n-1时的大，所有这个数组是个最优子数组，有点dp的感觉
        // int primes[3] = {2,3,5};
        vector<int> uglys{1};// 代表i=0,j=0,k=0时的初始丑数
        
        // 这里进行了空间压缩，不需要记录每个prime因子组的值，记录i2，i3，i5就好了，很巧妙
        int i2 = 0, i3 = 0, i5 = 0;
        int ugly2, ugly3, ugly5;
        for (int i = 2; i <= n; ++i) {
            ugly2 = uglys[i2] * 2;
            ugly3 = uglys[i3] * 3;
            ugly5 = uglys[i5] * 5;
            // int uglyM = max(ugly2, max(ugly3, ugly5));// 第n次的丑数是当前三个丑数中最小的
            int uglyM = min(ugly2, min(ugly3, ugly5));
            // 如果出现6的时候，要更新i2和i3
            if (uglyM == ugly2) ++i2;
            if (uglyM == ugly3) ++i3;
            if (uglyM == ugly5) ++i5;
            
            // 别忘了将新产生的数加入到uglys
            uglys.push_back(uglyM);
        }

        return uglys.back();
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;
    
    rtn = gua.nthUglyNumber(10);
    cout << "expect value = 12, actual value = " << rtn << endl;

    rtn = gua.nthUglyNumber(1);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
