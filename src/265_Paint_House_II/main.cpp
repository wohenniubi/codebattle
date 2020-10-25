
#include <iostream>
#include <vector>

using namespace std;

class Solution1 {
public:
    //Runtime: 36 ms, faster than 54.96%
    //Memory Usage: 11.6 MB, less than 5.36%
    //DP背包问题，但是时间复杂度是O(k*k*n), 题目要求是O(kn)，实在想不到巧妙的办法如何坚决j!=k的操作
    //min(dp[i-1][j] + cost[i][k] | j in range(k) but j != k, dp[i-1][k])
    int minCostII(vector<vector<int>>& costs) {
        int nhouse = costs.size();
        if (!nhouse) return 0;
        int kcolor = costs[0].size();
        if (!kcolor) return 0;
        if (kcolor == 1) {
            //assert(nhouse == 1);
            return costs[0][0];//有个测试用例是[[8]]
        }
        
        vector<int> prices(kcolor);//初始化为0，空间压缩
        for (int i = 0; i < nhouse; ++i) {
            vector<int> oldprices = prices;
            // prices = vector<int>(kcolor, INT_MAX);// 空间换时间
            
            for (int k = 0; k < kcolor; ++k) {
                prices[k] = INT_MAX;
                for (int j = 1; j < kcolor; ++j) {
                    int tmp = (k + j)%kcolor;
                    //prices[i][k] = min(prices[i-1][j] + costs[i][k] | j!=k);
                    prices[k] = min(oldprices[tmp] + costs[i][k], prices[k]);
                }
            }
        }
        
        int rtn = INT_MAX;
        for (int k = 0; k < kcolor; ++k) rtn = min(rtn, prices[k]);
        return rtn;
    }
};

class Solution {
public:
    //Runtime: 24 ms, faster than 98.69%
    //Memory Usage: 11.2 MB, less than 5.22%
    //min(dp[i-1][j] + cost[i][k] | j in range(k) but j != k, dp[i-1][k])
    int minCostII(vector<vector<int>> &costs) {
            // 在方法1的基础上，为了避免再使用一个for loop来处理
            // min(dp[i-1][j]+cost[i][k]| j in range(0,color#) && j!=k)，
            // 这里利用了最小和次小的cost以及最小cost对应的color来filter那个j==k，非常巧妙的greedy
            int minstCost = 0, minerCost = 0, kargmin = -1;
            for (int i = 0; i < costs.size(); ++i) {
                // 内部for loop这么定义还顺便完成了初始化，非常的巧妙简洁
                int minstTmp = INT_MAX, minerTmp = INT_MAX, kargTmp = -1;
                
                for (int j = 0; j < costs[i].size(); ++j) {
                    // 将当前颜色与上一个房子的颜色进行比较
                    int cost = costs[i][j] + ((j == kargmin)? minerCost: minstCost);
                    if (cost < minstTmp) {
                        // 小于最小，则要更新次小和kargTmp
                        minerTmp = minstTmp;
                        minstTmp = cost;
                        kargTmp = j;
                    } else if (cost < minerTmp) {
                        minerTmp = cost;//不需要改变最小的cost，不需要保存次小的颜色
                    }
                }
                minstCost = minstTmp, minerCost = minerTmp, kargmin = kargTmp;
            }
            return minstCost;
        }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> costs;
    
    rtn = gua.minCostII(costs={{8}});
    cout << "expect value = 8, actual value = " << rtn << endl;
    
    rtn = gua.minCostII(costs={{1,5,3}, {2, 9, 4}});
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    return 0;
}
