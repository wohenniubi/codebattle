#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // Runtime: 276 ms, faster than 33.03%
  // Memory Usage: 88 MB, less than 5.00%
  int maxProfit(vector<int>& prices) {
        // 背包问题？
        int days = prices.size();
        vector<int> buy1(days), sel1(days), buy2(days), sel2(days);
        
        // buy1[0] = -prices[0];
        buy1[0] = buy2[0] = -prices[0];
        for (int i = 1; i < days; ++i) {
            buy1[i] = max(buy1[i-1], -prices[i]);
            sel1[i] = max(sel1[i-1], buy1[i-1] + prices[i]);
            
            // if (i > 1)
            buy2[i] = max(buy2[i-1], sel1[i-1] - prices[i]);
            // if (i > 2)
            sel2[i] = max(sel2[i-1], buy2[i-1] + prices[i]);
        }
        
        // return max(sel1.back(), sel2.back());
        return sel2.back();
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> prices;

  rtn = gua.maxProfit(prices={1,2,3,4,5});
  cout << "expect value = 4, actuval value = " << rtn << endl;
  return 0;
}

