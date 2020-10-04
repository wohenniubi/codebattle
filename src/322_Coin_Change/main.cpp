#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    // 这里amount等价于拆分字符串那道题里面的s和pos, 它自身就同时包含了两个功能, 
    // (1) 告知递归是否结束, (2) 指导更深一层的递归该如何调用
    int helper(vector<int>& coins, int amount, unordered_map<int, int> &dict) {
        if (amount == 0) return 0;// 先姑且返回0;
        if (amount < 0) return -1;
        
        if (dict.count(amount)) return dict[amount];
        
        int rtn = INT_MAX;
        for (auto coin : coins) {
            //if (coin > amount) continue;
            int tmp = helper(coins, amount-coin, dict);
            if (tmp >= 0)
                rtn = min(rtn, tmp+1);
        }
        // return dict[amount] = (rtn == 0 )? -1: rtn;
        // 这里有个小trick, 如何使用一个int表示可以拼凑和不可以拼凑, 就是以下的办法
        // 返回-1表示无法拼凑, 返回正数表示可以拼凑;
        // for循环里面代码为了统一, 使用tmp+1, 因此返回-1时需要处理两种情况, 
        // 一种是拆分了之后剩余的部分不能拼凑rtn=0, 一种是本身无法拼凑rtn=INT_MAX
        return dict[amount] = (rtn == INT_MAX)? -1: rtn;
    }
    
    int coinChange1(vector<int>& coins, int amount) {
        unordered_map<int, int> dict;
        //sort(coins.begin(), coins.end(), greater<int>());
        return helper(coins, amount, dict);        
    }
    
    //  完全背包问题
    //Runtime: 56 ms, faster than 96.29% 
    //Memory Usage: 14.3 MB, less than 25.75%
    int coinChange(vector<int>& coins, int amount) {
        // TODO: 初始化
        vector<int> dp(amount+1, -1);// 初始化为0的好处：对于[1],0，返回0不用做特殊处理
        if (amount == 0) return 0;
        
        for (auto coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                // 因为要凑整，所以条件相对要苛刻一些
                if (i == coin) {
                    // 1.要在硬币面值等于i值时才更新dp
                    dp[i] = 1;// 一步到位实现最小
                } else if (dp[i-coin] != -1) {
                    // 2.更新其他dp时，因为min，所以要避开不能凑整(初始值)的情况
                    if (dp[i] != -1)
                        dp[i] = min(dp[i-coin]+1, dp[i]);
                    else 
                        dp[i] = dp[i-coin]+1;
                } // 其他情况下，dp[i] = dp[i]', 由于压缩了空间, 所以就是值不变
                
                // if (dp[i] == -1) {
                //     dp[i] = 1;// 至少要更新一下嘛，要不然一直是0
                // } else {
                //     dp[i] = min(dp[i-coin]+1, dp[i]);
                // }
            }
        }
        return dp[amount];
    }
};

int main(int argc, const char * argv[]) {
  Solution gua;
  int rtn, amount;
  vector<int> coins;
  rtn = gua.coinChange(coins={1,2,5}, amount=11);
  cout << "expect value = 3, actual value = " << rtn << endl;

  rtn = gua.coinChange(coins={2}, amount=3);
  cout << "expect value = -1, actual value = " << rtn << endl;

  rtn = gua.coinChange(coins={1}, amount=0);
  cout << "expect value = 0, actual value = " << rtn << endl;
  return 0;
}

