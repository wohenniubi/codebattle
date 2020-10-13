
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    // 首先想想规律，直觉上想到要先分为奇数和偶数
    // 如果是偶数，可以copy all(c) + paste(p)，例如
    // 2 -> c + p = 2
    // 4 -> c + p + c + p = 4
    // 8 -> c + p + c + p + c + p = 6  2*log2(n)
    // 如果是奇数，2*n + 1
    // 1 -> 0
    // 3 -> c + p + p = 3
    // 6 -> 3 * 2 -> c + p + p + c + p = 5
    // 5 -> c + p + p + p + p = 5
    // 7 -> c + p + p + p + p + p + p = 7
    // 9 -> 3 * 3 -> c + p + p + c + p + p = 6
    // 10-> 5 * 2 -> c + p + p + p + p + c + p = 7
    // 11-> c + p + p + p + p + p + p + p + p + p + p = 11
    // 12-> 6 * 2 or 3 * 4 or 4 * 3 -> 5 + 2 or 3 + 4 or 4 + 3
    // 13-> c + p + p + p + p + p + p + p + p + p + p + p + p = 13
    // 14-> 7 * 2 -> c + p + p + p + p + p + p + c + p = 9
    // 有点意思哟，貌似如果是质数prime#，那么就是其本身；
    // 如果不是质数，那么就拆分为两个因子，把大的放在前面，然后调用前面的结果，再加第二个因子
    // 然后对于1，返回0；
    // 那么就是找1～1000里面的质数，然后对于非质数，进行因式分解，这貌似是有一道leetcode的题
    // 然后一提到质数，就应该想到sqrt，然后有递归和迭代两种实现
    //Runtime: 8 ms, faster than 48.90%
    //Memory Usage: 6.9 MB, less than 5.11%
    int minSteps1(int n) {
        if (n == 1) return 0;
        
        int num = sqrt(n);// 计算背包物品的个数，floor(sqrt(n))
        // vector<int> dp(num+1);// 为了方便，多加1位
        vector<int> dp(n+1);// 大意啦大意啦！！price是n
        
        // dp[1] = ;//初始化应该等于啥，要不算不出来哟
        // for (int i = 1; i <= n; ++i) {
        for (int i = 2; i <= n; ++i) {
            // dp[i] = i;// 很奇葩的操作，在这里初始化了
            // 这里内部loop是背包元素的个数，move只有一种判断是不是质数
            // for (int j = 1; j <= num; ++j) {
            for (int j = 2; j <= num; ++j) {
                if (i%j == 0) {
                    // 因为j是从小到大的，所以正好dp[j]放在前面合理，小的放在前面
                    dp[i] = dp[j] + dp[i/j];
                }
            }
            if (dp[i] == 0) dp[i] = i;//质数
        }
        return dp[n];
    }
    
    // 递归做法，超级快而且省空间，原因是这里不需要计算多余的dp数组，另外由于借助于递归，
    // 这里隐含了一个哈希表，是真正意义上的O(1)时间复杂度，所以结果才即省时间又省空间。
    // 不过第一次应该想不到这样做，而且实际应用中这样的代码过于针对，只要改一点条件就不work
    // 当作拓展思维吧
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.3 MB, less than 5.11%
    int minSteps(int n) {
        if (n == 1) return 0;
        int num = sqrt(n);
        // 背包问题的递归框架，外部循环由递归之前更新price值来控制，
        // 内部循环遍历所有的背包物品，这里是n所有可能的因子，超过sqrt(n)之后就会重复，
        // 而本题需要把小因子放前面，所以遍历到sqrt就救赎，合理
        for (int i = 2; i <= num; ++i) {
            if (n % i == 0) {
                // i是小因子对应的倍数，需要1次copy all + (i-1)次paste，所以小因子部分总共还是i
                //return i * minSteps(n/i);// 很大胆哟，直接返回
                return i + minSteps(n/i);// 不要大意啊！
            }
        }
        return n;// 跳出则表明是质数，直接返回n
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;
    
    rtn = gua.minSteps(n = 1);
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.minSteps(n = 3);
    cout << "expect value = 3, actual value = " << rtn << endl;
    
    rtn = gua.minSteps(n = 9);
    cout << "expect value = 6, actual value = " << rtn << endl;
    
    rtn = gua.minSteps(n = 11);
    cout << "expect value = 11, actual value = " << rtn << endl;
    
    return 0;
}
