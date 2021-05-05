
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Solution {
public:
    long gcd(long a, long b) {
        return (0 == b)? a : gcd(b, a%b);
    }
    // a*b = gcd(a,b) * lcm(a,b)
    long lcm(long a, long b) {
        return (a/gcd(a,b))*b;
    }
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.8 MB, less than 65.64%
    int nthUglyNumber(int n, int a, int b, int c) {
        long ab = lcm(a,b);
        long bc = lcm(b,c);
        long ac = lcm(a,c);
        long abc = lcm(ab, c);// 在计算a=2, b = 217983653, c = 336916467的lcm时int溢出，所以要用long
    
        // 这里用到了一个规律
        // part1. 小于等于x的所有a的倍数的个数 = x/a
        // part2. 小于等于x的所有b的倍数的个数 = x/b
        // part3. 小于等于x的所有c的倍数的个数 = x/c
        
        // 那么小雨等于x的能被a，b和c整除的数的个数等于，范得蒙公式
        // part1 + part2 + part3 - part1&part2 - part1&part3 - part2&part3 + part1&part2&part3
        // 然后注意abc可能不适互斥，所以要使用lcm
        
        // 使用二分查找减少复杂度
        int l = 1, r = INT_MAX;
        while (l < r) {
            int mid = l + (r-l)/2;// 取一个中间数，看小于等于它的数个数是否等于n
            int cnt = mid/a + mid/b + mid/c - mid/ab - mid/ac - mid/bc + mid/abc;
            if (cnt == n) {
                //return mid;// 错误，由于mid/a是向下取整，因此52和49得到的cnt都等于7，不能返回，要继续压缩区间
                r = mid;
            } else if (cnt > n) {
                // 说明mid是上限，先设置得不变吧
                r = mid;
            } else {
                // cnt < n
                l = mid + 1;// 说明肯定要比l大的数才有可能达到个数等于n
            }
        }
        return l;
    }
    
    // 以下方法仅对于a，b，c互斥的情况，对于n = 4, a = 2, b = 3, c = 4搞不定
    int nthUglyNumber1(int n, int a, int b, int c) {
        // 要不把第0个ugly number当作1
        // 然后还是x = (a^i)*(b^j)*(c^k)的操作
        
        // 这里的memo其实是dp，是在for循环过程中计算得到的
        //static vector<int> memo{1};// 把memo放在heap上面，这是不行的，因为a，b，c会发生变化
        unique_ptr<vector<int>> memo(new vector<int>{1});
        int i = 0, j = 0 , k = 0;
        
        // 如果大于n则不需要计算，直接提取就好
        //if (memo.size() <= n) {
            auto dp = *(memo.get());
            for (int cnt = 1; cnt <= n; ++cnt) {
                long long tmpa = dp[i] * a;
                long long tmpb = dp[j] * b;
                long long tmpc = dp[k] * c;
                // 取的是三个因子扩大后的最小值
                long long tmpM = min(min(tmpa, tmpb), tmpc);
                if (tmpa == tmpM) ++i;
                if (tmpb == tmpM) ++j;
                if (tmpc == tmpM) ++k;
                dp.push_back(tmpM);
            }
        //}
        return dp[n];
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n, a, b, c;
    rtn = gua.nthUglyNumber(n = 7, a = 7, b = 7, c = 7);
    cout << "expect value = 49, actual value = " << rtn << endl;

    rtn = gua.nthUglyNumber(n = 5, a = 2, b = 11, c = 13);
    cout << "expect value = 10, actual value = " << rtn << endl;

    rtn = gua.nthUglyNumber(n = 4, a = 2, b = 3, c = 4);
    cout << "expect value = 6, actual value = " << rtn << endl;

    rtn = gua.nthUglyNumber(n = 3, a = 2, b = 3, c = 5);
    cout << "expect value = 4, actual value = " << rtn << endl;

    return 0;
}
