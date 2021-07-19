
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 83.80%
    //Memory Usage: 10.7 MB, less than 11.73%
    double new21Game(int n, int k, int maxPts) {
        if (n < k) return 0.0;// 要到sum总数为k才会停止，而n小于k，那么所有的情况都让sum <= n不成立，故返回0
        if (k == 0) return 1.0;// 如果不允许抽牌，那么sum必然小于等于n, n大于等于0，所以满足小于等于n，故返回100%
        // 在k-1时还可以抽牌，而最大抽牌maxPts，所以能达到的最大sum是k-1+maxPts；故如果n大于等于这个值，所有情况都满足<=n
        if (n >= k-1+maxPts) return 1.0;
        
        vector<double> dp(k + maxPts);// dp的意义是手牌总数为i时，在sum为k或者大于k时停止，sum小于等于n的概率
        
        // 然后初始化，仅仅把一部分dp值设置为1.0，没毛病
        for (int i = k; i <= n; ++i)
            dp[i] = 1.0;// 手牌数达到k之后不能再抽牌，此时对于小于等于n的那些情况，就是dp的定义，因此dp[i]设置为1.0
        
        // 现在开始倒序计算[0,k)这部分的dp值，这里由于每次都是固定的窗，因此可以利用错位序列的小技巧，减少一层for循环
        double sum = n - k + 1;// 前面那部分共有 n-k+1那么多个1，因此可以计算出那部分的sum
        
        for (int i = k-1; i >= 0; --i) {
            // dp[i] = (dp[i+1] + dp[i+2] + ... dp[i+maxPts])/maxPts
            dp[i] = sum/maxPts;//dp[i+1]到dp[i+maxPts]这maxPts个数的sum已经计算在sum里面
            
            // dp[i-1] = (dp[i] + dp[i+1] + ... dp[i+maxPts-1])/maxPts
            // 为了下次计算dp[i-1]，由于还是需要maxPts个数之和，所以利用错位关系，可以可以更新sum
            sum = sum - dp[i+maxPts] + dp[i];
        }
        
        return dp[0];
    }
    
    // 方法2: dp解法
    double new21Game1(int N, int K, int W) {
        if (K == 0 || N >= K + W) return 1.0;
        vector<double> dp(K + W);
        
        dp[0] = 1.0;
        for (int i = 1; i < K + W; ++i) {
            dp[i] = dp[i - 1];
            if (i <= W) dp[i] += dp[i - 1] / W;
            else dp[i] += (dp[i - 1] - dp[i - W - 1]) / W;
            if (i > K) dp[i] -= (dp[i - 1] - dp[K - 1]) / W;
        }
        return dp[N] - dp[K - 1];
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    double rtn;
    int N, K, W;
    rtn = gua.new21Game(N = 10, K= 1, W = 10);
    cout << "expect value = 1.0, actual value = " << rtn << endl;

    rtn = gua.new21Game(N = 6, K= 1, W = 10);
    cout << "expect value = 0.6, actual value = " << rtn << endl;

    rtn = gua.new21Game(N = 21, K= 17, W = 10);
    cout << "expect value = 0.73278, actual value = " << rtn << endl;

    return 0;
}
