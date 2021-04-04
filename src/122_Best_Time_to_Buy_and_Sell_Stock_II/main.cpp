#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 90.87%
    //Memory Usage: 13.2 MB, less than 27.74%
    int maxProfit(vector<int>& prices) {
        // dp问题，拿到就想状态是啥，其中一个是天数，另一个根据题意，就设置为目前为止的卖出最大收益，还有一个是目前为止买入的最大收益
        int size = prices.size();
        vector<int> sell = vector<int>(size);
        vector<int> buyy = vector<int>(size);

        buyy[0] = -prices[0];
        for (int i = 1; i < size; ++i) {
            sell[i] = max(sell[i-1], prices[i]+ buyy[i-1]);
            buyy[i] = max(buyy[i-1], sell[i-1]- prices[i]);
        }
        return sell.back();
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> prices;

  rtn = gua.maxProfit(prices = {7,1,5,3,6,4});
  cout << "expect value = 7, actual value = " << rtn << endl;

  rtn = gua.maxProfit(prices = {1,2,3,4,5});
  cout << "expect value = 4, actual value = " << rtn << endl;

  rtn = gua.maxProfit(prices = {7,6,4,3,1});
  cout << "expect value = 0, actual value = " << rtn << endl;

  return 0;
}

