#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 192 ms, faster than 95.27% 
    //Memory Usage: 60.1 MB, less than 14.73%
    int maxProfit1(vector<int>& prices, int fee) {
        // 交易费是在卖出时出现的
        // 还是无限背包问题
        int days = prices.size();
        // vector<int> buys(days), sell(days), cool(days); //没有cooldown呀，别背题
        vector<int> buys(days), sell(days);
        
        buys[0] = -prices[0];//初始化很重要
        // sell和cool在第一天是没有意义的，初始化为0合理
        for (int i = 1; i < days; ++i) {
            buys[i] = max(buys[i-1], sell[i-1]-prices[i]);
            sell[i] = max(sell[i-1], buys[i-1]+prices[i] - fee);
            // cool[i] = max(cool[i-1], sell[i-1]);
        }
        // return max(sell.back(), cool.back());
        return sell.back();
    }

    //Runtime: 192 ms, faster than 95.27% 
    //Memory Usage: 55.3 MB, less than 47.25%
    int maxProfit(vector<int>& prices, int fee) {
        int days = prices.size();
        // vector<int> buys(days), sell(days), cool(days); //没有cooldown呀，别背题
        // vector<int> buys(days), sell(days); // 空间压缩！
        // buys[0] = -prices[0];//初始化很重要
        
        int buys = -prices[0], sell = 0;
        // sell和cool在第一天是没有意义的，初始化为0合理
        for (int i = 1; i < days; ++i) {
            int temp = buys;
            // buys[i] = max(buys[i-1], sell[i-1]-prices[i]);
            // sell[i] = max(sell[i-1], buys[i-1]+prices[i] - fee);
            buys = max(buys, sell - prices[i]);
            sell = max(sell, temp + prices[i] - fee);
            // cool[i] = max(cool[i-1], sell[i-1]);
        }
        // return max(sell.back(), cool.back());
        // return sell.back();
        return sell;
    }
};

int main() {
  Solution gua;
  int rtn, fee;
  vector<int> prices;

  rtn = gua.maxProfit(prices={1,3,2,8,4,9}, fee=2);
  cout << "expect value = 8, actual value = " << rtn << endl;

  return 0;
}
