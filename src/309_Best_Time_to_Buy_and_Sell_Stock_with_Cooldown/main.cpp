#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;// 有个corner case 输入为[]

        // 完全背包问题？而且是有顺序的
        int days = prices.size();
        vector<vector<int>> dp(3,vector<int>(days));

        // dp[0], dp[1], dp[2]分别代表最后一次move是买入，卖出，冷却的最大值
        // 牢记dp[i][j]表示的是dp[i]这个操作序列中，第j天时的最大价值，
        // 注意不是用dp[i]与dp[i-1]比较，状态转移方程如下：
        // dp[0] = f1(dp[2])
        // dp[1] = f2(dp[0])
        // dp[2] = f3(dp[1], dp[2])
        dp[0][0] = -prices[0];// 这一步非常重要啊！！没这步就做不出来

        // 因为要保证顺序，因此从左到右更新
        for (int i = 1; i < days; ++i) {

            dp[0][i] = max(dp[0][i-1], dp[2][i-1] - prices[i]);//-1,-1,-1,1,0
            // TODO: 再想想
            dp[1][i] = max(dp[1][i-1], dp[0][i-1] + prices[i]);//0, 1, 2, 2,3
            dp[2][i] = max(dp[2][i-1], dp[1][i-1]);            //0, 0, 1, 2,2
            //for (int j = 0; j < 3; ++j) {
            //}
        }
        //return max(max(dp[0].back(), dp[1].back()),dp[2].back());
        //最后这一步才是在dp[0],dp[1]和dp[2]之间进行比较，
        //由于要赚得最多，肯定不要手里有股票，所以可以简化为比较dp[1]和dp[2]
        return max(dp[1].back(), dp[2].back());
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> prices;
  rtn = gua.maxProfit(prices={});
  cout << "expect value = 0, actual value = " << rtn << endl;

  rtn = gua.maxProfit(prices={1,2,3,0,2});
  cout << "expect value = 3, actual value = " << rtn << endl;

  rtn = gua.maxProfit(prices={1,2,4});
  cout << "expect value = 3, actual value = " << rtn << endl;

  return 0;
}

