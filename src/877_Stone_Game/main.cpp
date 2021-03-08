
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 这个递归函数的基本定义是[l,r]区间内的minimax值；时间复杂度O(n^2)，因为需要计算l到r范围内的dp子问题，l,r范围都是n
    //Runtime: 28 ms, faster than 27.24%
    //Memory Usage: 16.5 MB, less than 22.10%
    int minimax(vector<int> &piles, int l, int r, vector<vector<int>> &dp) {
        if (l == r) return piles[l];
        if (dp[l][r]) return dp[l][r];
        
        // 由于只有两个player，且每个player都希望获得最大值，所以不存在maximin的操作
        // 所以wiki上的伪代码可以去掉其中的一半分支；
        // 再机智的计算相对值，可以省去计算player1和player2各自的sum，也就会避开len(piles)过大时的溢出问题
        dp[l][r] = max(piles[l] - minimax(piles, l+1, r, dp),
                      piles[r] - minimax(piles, l, r-1, dp));
        
        return dp[l][r];
    }
    
    //Runtime: 20 ms, faster than 40.05%
    //Memory Usage: 16.2 MB, less than 32.44%
    bool stoneGame(vector<int>& piles) {
        // 这道题是典型的minimax问题，说白了也就是决策树的遍历问题，因此也有返回条件，分支遍历等
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n));
        // 方法1，memo + 递归
        // return minimax(piles, 0, n-1, dp) > 0;// 没有tie所以不会等于0
        
        // 方法2，memo + 迭代：为了压缩空间，一般来讲是先写成迭代形式
        // 基本思路不变，dp还是用于保存相对值，首先初始化对角线上的值，这些对应len=1的数组，
        for(int i = 0; i < n; ++i)
            dp[i][i] = piles[i];
        
        // 然后从对角线想着右上角迭代求解，很fancy的做法，本质还是minimax
        for (int len = 2; len <= n; ++len) {
            // 这里i从第0位开始，最长只能到n-len，因为如果超过这个值，那么在长度为len的情况下，j=i+len-1就会越界
            for (int i = 0; i <= n-len; ++i) {
                int j = i+len-1;
                dp[i][j] = max(piles[i] - dp[i+1][j], piles[j] - dp[i][j-1]);
                // 例如：len=2时，dp[0][1] = max(piles[0] - dp[1][1], piles[1] - dp[0][0])
            }
        }
        return dp[0][n-1] > 0;
    }
};


int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> piles;
    rtn = gua.stoneGame(piles = {5,4,3,5});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
