#include <iostream>
#include <vector>
#include <tuple>    // 是pair的升级，可以多于两个参数

using namespace std;

class Solution {
public:
    //Runtime: 172 ms, faster than 29.18%
    //Memory Usage: 20.1 MB, less than 9.01%
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        const int kInf = 1e9+7, s = 1;
        // 这里的状态包括：小区数，前m个房子，某种颜色结尾，存的是最小cost，因为目的是求最小，所以初始化为max
        vector<vector<vector<int>>> dp(target+1, vector<vector<int>>(m+1,vector<int>(n+1,kInf)));
        
        dp[0][0][0] = 0;// 大意了，这里不仅仅是这个点
        fill(dp[0][0].begin(), dp[0][0].end(), 0);
        for (int k = 1; k <= target; ++k) {
            // 抽屉原理剪支，至少要有k个房子，才能保证k个小区
            for (int i = k; i <= m; ++i) {
                // 然后要用第i个house的颜色与i-1个房子的颜色进行比较
                // 比较过程中需要考虑已经填充的颜色，因此把i-1个房子的颜色罗列出来，这里的复杂度就是O(n*n)
                int hci = houses[i-1];// -1是因为index的缘故
                int hcj = (i>=2)? houses[i-2] : 0;// j = i-1
                //tuple<int, int> mytuple;
                //auto [si, hi] = tie(hci, hcj);
                // 这里通过考虑房子是否涂色，找到了i-1个房子和i个房子的颜色范围
                const auto [li, ui] = hci? tie(hci, hci) : tie(s, n);//直接使用tie(1,n)会报错
                const auto [lj, uj] = hcj? tie(hcj, hcj) : tie(s, n);
//                const auto &[si, hi] = hci? tie(hci, hci): tie(1,n);
//                const auto [sj, hj] = hcj? tie();
                for (int ci = li; ci <= ui; ++ci) {
                    // 如果hci和hcj相同，
                    // dp[k][i][ci]= dp[k][i-1][cj] + cost[i], 这里cost[i]=hci?0:cost[i][hci]
                    // 否则
                    // dp[k][i][ci]= dp[k-1][i-1][cj]+cost[i], 这里cost[i]=hci?0:cost[i][hci]
                    int v = hci?0:cost[i-1][ci-1];
                    for (int cj = lj; cj <= uj; ++cj) {
                        dp[k][i][ci] = min(dp[k][i][ci], dp[k-(ci!=cj)][i-1][cj] + v);
                    }
                    // 内部cj loop结束之后得到以ci结尾的最小cost，dp[k][i][ci]
                }
                // 外部ci loop结束之后得到最小cost数组dp[k][i][*]
            }
        }
        // 结束之前，把dp[target][m][*]整理一下，得到最小值
        int rtn = *min_element(dp[target][m].begin(), dp[target][m].end());
        return (rtn >= kInf)? -1:rtn;
        //return -1;
    }

    // backtracking的方法不行
    int minCost1(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // 这道题看似很多限制，但是限制本身是可以让问题的思考方向更加明确，也就是所谓的greedy思维
        // 首先从color入手，可以通过已经存在颜色的房子，确定neighbor个数，然后再按照传统的Kth sum group来解决
        // m和n的范围分别是100和20，O(m*n*m)的复杂度应该可以承受
        
        int num = 0;
        houses.push_back(0);
        for (int i = houses.size()-2; i >= 0; --i) {
            if (houses[i] && (houses[i] != houses[i+1]))
                num++;
        }
        if (num > target) {
            houses.pop_back();
            return -1; // [3,1,2,3] target = 3的例子，直接返回
        }
        
        // 然后把问题划分为子问题：从index到houses.size()的房子，在给定小区个数的情况下的最小值
        int rtn = backTrackCost(houses, houses.size()-2, cost, m, n, target, 0);
        houses.pop_back();
        return rtn;
    }
    
    // 这里houses就是visited数组
    int backTrackCost(vector<int> &houses, int indx, vector<vector<int>> &cost, int m, int n, int target, int sum) {
        if (target < 0) return -1;
        if (indx < 0) return ((target == 0)? sum:-1);//此时要达到目标target
        
        // 现在就是合法的操作了，开心; 下面的循环是colors（决策），然后由迭代来控制path的长度
        if (houses[indx]) return backTrackCost(houses, indx-1, cost, m, n, target, sum);
        
        // 这个位置没有填色，n个颜色任选
        int minSum = INT_MAX;
        for (int i = 0; i < n; ++i) {
            houses[indx] = i+1;// 填一个颜色，注意颜色是1-index
            //if (houses[indx] != houses[i+1]) { 大意了，居然这里写成i了，i是color
            if (houses[indx] != houses[indx+1]) {
                target--;
            }
            
            if (indx >= target) {
            // if (indx < target) {
            //     goto NEXT_COLOR;// 表明即使把剩下的houses都涂成不同的颜色，也不能凑出target个小区，跳到下一个选择
            //     // 跳过tmp这个初始化了，所以要把tmp放在goto之前，或者把后面的操作放在else里面
            // } else {
                int tmp = backTrackCost(houses, indx-1, cost, m, n, target, sum+cost[indx][i]);
                if (tmp > -1) {
                    minSum = min(minSum, tmp);
                }
            }
            //NEXT_COLOR:
            if (houses[indx] != houses[i+1]) {
                target++;
            }
            // 大意了，因为houses是复用的，记得把颜色修改为0呀
            houses[indx] = 0;
        }
        return (minSum == INT_MAX)? -1: minSum;
    }
};

class Solution2 {
public:
    // 网上的另一个解法，我唯一觉得有趣的是这里使用了function关键字作为lambda函数的返回值类型
    // 语法是返回值类型(输入1类型,输入2类型...)，然后[&]这里的是对当前非global变量的引用
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        int dp[21][100][101];
        for (auto& plane : dp) for (auto& row : plane) for (auto& x : row) x = -2;
        function<int(int,int,int)> dfs = [&](int i, int j, int k) {
            if (j == m) {
                if (k == 0) return 0;
                else return -1;
            }
            if (k < 0) return -1;
            if (dp[i][j][k] != -2) return dp[i][j][k];
            if (k > m - j) return dp[i][j][k] = -1;
            if (houses[j] != 0) {
                if (houses[j] == i)
                    return dp[i][j][k] = dfs(i, j+1, k);
                else
                    return dp[i][j][k] = dfs(houses[j], j+1, k-1);
            } else {
                int res = INT_MAX, t;
                if (i != 0) {
                    t = dfs(i, j+1, k);
                    if (t != -1) res = min(res, t + cost[j][i-1]);
                }
                if (k > 0) {
                    for (int r = 1; r <= n; r++) {
                        if (r != i) {
                            t = dfs(r, j+1, k-1);
                            if (t != -1) res = min(res, t + cost[j][r-1]);
                        }
                    }
                }
                if (res == INT_MAX) res = -1;
                return dp[i][j][k] = res;
            }
        };
        return dfs(0, 0, target);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int m, n, target, rtn;
    vector<vector<int>> cost;
    vector<int> houses;

    houses = vector<int>({0,2,1,2,0});
    cost = vector<vector<int>>({{1,10},{10,1},{10,1},{1,10},{5,1}});
    rtn = gua.minCost(houses, cost, m=5, n=2, target=3);
    cout << "expect value = 11, actual value = " << rtn << endl;

    houses = vector<int>({0,0,0,0,0});
    cost = vector<vector<int>>({{1,10},{10,1},{10,1},{1,10},{5,1}});
    rtn = gua.minCost(houses, cost, m=5, n=2, target=3);
    cout << "expect value = 9, actual value = " << rtn << endl;
    //std::cout << "Hello, World!\n";
    return 0;
}

