
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    #define MYMODE 1000000007
    
    // 稍加改动递推关系 dp[n][k] = dp[n - 1][k] + dp[n - 1][k-1] + ... + dp[n - 1][k - n + 1]
    // 用k+1代替k得到：dp[n][k+1] = dp[n - 1][k+1] + dp[n - 1][k] + ... + dp[n - 1][k + 1 - n + 1]
    // 两个等式相减得到：dp[n][k+1] = dp[n][k] + dp[n - 1][k+1] - dp[n - 1][k - n + 1]
    // 再把k+1替换回k：dp[n][k] = dp[n][k-1] + dp[n - 1][k] - dp[n - 1][k - n]
    // 只剩下有限个数据，那么递归或者迭代都可以，只需要注意最后一项要在k>=n时才有效
    //Runtime: 40 ms, faster than 48.70%
    //Memory Usage: 16.4 MB, less than 16.88%
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1, vector<int>(k+1));// 为了让index方便，于是增加了1
        // 初始化TODO，看能否解决几个case
        // n = 1, k =  0 -> rtn = 1
        // n = 1, k >= 1 -> rtn = 0
        // n = 2, k =  0 -> rtn = 1
        // n = 2, k =  1 -> rtn = 1
        // n = 2, k >= 2 -> rtn = 0
        // n = 3, k =  0 -> rtn = 1
        // n = 3, k =  1 -> rtn = 2 (1,3,2) (2,1,3)
        // n = 3, k =  2 -> rtn = 2 (3,1,2) (2,3,1)
        // n = 3, k =  3 -> rtn = 1 (3,2,1)
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 1;
        for (int j = 1; j <= k; ++j)
            dp[0][j] = 0;
        
        for (int i = 1; i <= n; ++i) {
            // 还有一种做法是在这里设置dp[i][0] = 1，这样的话就不用上面的两个初始化操作了
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = (dp[i][j-1] + dp[i-1][j])%MYMODE;

                if (j >= i)
                    //dp[i][j] = (dp[i][j] - dp[i-1][j-i])%MYMODE; 这样还是不得行，会出现负数
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + MYMODE)%MYMODE;
            }
        }
        
        return dp[n][k];
    }
    
    // 以下操作会超时，貌似是因为每一级都是O(k)个数，总共有O(k)级
    int dfs(int n, int k, unordered_map<int, int> &memo) {
        if (k < 0) return 0;// 忘记对这个corner case进行判断了
        if (k == 0) return 1;
        if (n == 0) return 0;
        if (n == 1) return (k>=1)?0:1;

        int key = n * 10000 + k;
        if (memo.count(key))
            return memo[key];
        
        int rtn = 0;
        for (int i = 0; i < n; ++i) {
            rtn += (dfs(n-1, k-i, memo) % MYMODE);
            rtn %= MYMODE;
        }
        
        return memo[key] = rtn;
    }
    
    int kInversePairs_time(int n, int k) {
        // 非常tricky的一道题，看着这种类型的题，貌似只能用dp
        //vector<vector<int>> dp(n, vector<int>(k));
        unordered_map<int, int> memo;
        
        // dp与两个状态有关，dp[n][k]表示从1到n个数，具有k个reverse pair的组合个数
        // 难点是如何找到dp[n][k]的递推关系，有点烧脑，先具像化，让n=3，看看它与dp[n+1][k]的关系
        
        // dp[4][k]的array相较于dp[3][k]的array，新增了4这个数，而4可以添加在长度为3的数组的4个位置，因此4个数的array组成如下：
        // 4在第3位，xxx4：不会影响xxx这组array的reverse pairs个数，即还是k，而这些array的个数正好是dp的定义，dp[3][k]
        // 4在第2位，yy4y：这会让yyy这组array的reverse pairs个数增加1，那么为了让加入4之后的pairs个数凑成k，
        // 于是要找到长度为3、且reverse pairs个数等于k-1的那些array，这些array的个数正好是定义dp[3][k-1]
        // 4在第1位，z4zz：这会让zzz这组array的reverse pairs个数增加2，那么为了让加入4之后的pairs个数凑成k，
        // 于是要找到长度位3、且reverse pairs个数等于k-2的那些array，这些array的个数正好是定义dp[3][k-2]
        // 4在第0位，4www：这些array的个数正好是定义dp[3][k-3]；而加上4之后，四个位置的array都不相同，所以是叠加
        
        // dp[n+1][k] = dp[n][k] + dp[n][k-1] + dp[n][k-2] +... dp[n][k-n]
        // 初始值怎么弄；
        // n = 1, k =  0 -> rtn = 1
        // n = 1, k >= 1 -> rtn = 0
        // n = 2, k =  0 -> rtn = 1
        // n = 2, k =  1 -> rtn = 1
        // n = 2, k >= 2 -> rtn = 0
        // n = 3, k =  0 -> rtn = 1
        // n = 3, k =  1 -> rtn = 2 (1,3,2) (2,1,3)
        // n = 3, k =  2 -> rtn = 2 (3,1,2) (2,3,1)
        // n = 3, k =  3 -> rtn = 1 (3,2,1)
        return dfs(n, k, memo);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    
    int rtn, n, k;
    rtn = gua.kInversePairs(n = 1000, k = 1000);
    cout << "expect value = 663677020, actual value = " << rtn << endl;

    rtn = gua.kInversePairs(n = 3, k = 1);
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.kInversePairs(n = 3, k = 0);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
