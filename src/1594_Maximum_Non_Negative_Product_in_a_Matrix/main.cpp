
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
//    #define MODULO (1e9+7)
    #define MODULO 1000000007
    
    //Runtime: 12 ms, faster than 63.10%
    //Memory Usage: 10.8 MB, less than 13.10%
    int maxProductPath(vector<vector<int>>& grid) {
        // 能够想得到的就是dp算法，而且由于每个move只能从上到下，从左到右
        // 因此可以有空间优化处理，省掉一维的空间
        int rows = grid.size();
        if (!rows) return 0;
        int cols = grid[0].size();
        
        // 貌似不能做空间优化，多一列操作，然后每一列的两行分别存最大值和最小值
        // 网上的另一种办法是使用两个vector<vector<int>> 数组分别存储最大值和最小值
//        vector<vector<pair<int,int>>> dp(rows+1,vector<pair<int,int>>(cols+1,{1,1}));
        vector<vector<pair<long long,long long>>> dp(rows+1,vector<pair<long long,long long>>(cols+1,{1,1}));
        
        for (int i = 1; i <= rows; ++i) {
            // for (int j = cols; j > 0; --j) {
            for (int j = 1; j <= cols; ++j) {
                // dp[i][j] = max(dp[i-1][j] + nums[j], dp[i][j-1] + nums[j]);
                // 更新最大值：最大值来源于左侧和上侧，左侧又等于max(最大值*val,最小值*val)
                if (i == 1) {
                    dp[i][j].first = dp[i][j-1].first * grid[i-1][j-1];
                    dp[i][j].second = dp[i][j].first;// 第一列只能从左到右
                } else if (j == 1) {
                    dp[i][j].first = dp[i-1][j].first * grid[i-1][j-1];
                    dp[i][j].second = dp[i][j].first;// 第一列只能从上到下
                } else {
                    //int tmp = grid[i-1][j-1];
                    long long tmp = grid[i-1][j-1];
                    long long leftmax = max(dp[i][j-1].first*tmp, dp[i][j-1].second*tmp);
                    long long updwmax = max(dp[i-1][j].first*tmp, dp[i-1][j].second*tmp);
                    // 貌似进行空间优化之后是一样的形式呢，这么开心

                    // 更新最小值：
                    long long leftmin = min(dp[i][j-1].first*tmp, dp[i][j-1].second*tmp);
                    long long updwmin = min(dp[i-1][j].first*tmp, dp[i-1][j].second*tmp);
                    dp[i][j].first = max(leftmax, updwmax);// % MODULO;
                    dp[i][j].second = min(leftmin, updwmin);// % MODULO;
                }
            }
        }
        //return (dp[rows][cols].first < 0)? -1: dp[rows][cols].first;
        //大意了，没明白得在最后才取模Notice that the modulo is performed after getting the maximum product.
        return (dp[rows][cols].first < 0)? -1: (dp[rows][cols].first % MODULO);
    }
   
    // 方法2是网上抄的，基本思路一样，操作时使用两个数组分别存储最大值和最小值，
    // 另外在更新当前位置grid[i][j]的值时，对符号进行了讨论，使得代码清晰了很多
    int maxProductPath2(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size(), MOD = 1e9+7;
        // we use long long to avoid overflow
        long long mx[m][n], mn[m][n];
        memset(mx,0,sizeof(mx));
        memset(mn,0,sizeof(mn));
        mx[0][0]=mn[0][0]=grid[0][0];
        
        // initialize the top and left sides
        for(int i=1; i<m; i++){
            mn[i][0] = mx[i][0] = mx[i-1][0] * grid[i][0];
        }
        for(int j=1; j<n; j++){
            mn[0][j] = mx[0][j] = mx[0][j-1] * grid[0][j];
        }

        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                if(grid[i][j] < 0){ // minimum product * negative number = new maximum product
                    mx[i][j] = (min(mn[i-1][j], mn[i][j-1]) * grid[i][j]);
                    mn[i][j] = (max(mx[i-1][j], mx[i][j-1]) * grid[i][j]);
                }
                else{ // maximum product * positive number = new maximum product
                    mx[i][j] = (max(mx[i-1][j], mx[i][j-1]) * grid[i][j]);
                    mn[i][j] = (min(mn[i-1][j], mn[i][j-1]) * grid[i][j]);
                }
            }
        }

        int ans = mx[m-1][n-1] % MOD;
        return ans < 0 ? -1 : ans;
    }

    // 方法1不work，貌似这种情况下没有办法进行空间压缩
    int maxProductPath1(vector<vector<int>>& grid) {
        // 能够想得到的就是dp算法，而且由于每个move只能从上到下，从左到右
        // 因此可以有空间优化处理，省掉一维的空间
        int rows = grid.size();
        if (!rows) return 0;
        int cols = grid[0].size();
        
        // 这里做了空间优化，多一列操作，然后每一列的两行分别存最大值和最小值
        vector<vector<int>> dp(2,vector<int>(cols+1,1));
        for (int i = 0; i < rows; ++i) {
            // for (int j = cols; j > 0; --j) {
            for (int j = 1; j <= cols; ++j) {
                // dp[i][j] = max(dp[i-1][j] + nums[j], dp[i][j-1] + nums[j]);
                // 更新最大值：最大值来源于左侧和上侧，左侧又等于max(最大值*val,最小值*val)
                if (i == 0) {
                    dp[0][j] = dp[0][j-1]*grid[i][j-1];
                    dp[1][j] = dp[0][j];// 第一行只能从左到右
                } else if (j == 1) {
                    dp[0][j] = dp[0][j]*grid[i][j-1];
                    dp[1][j] = dp[0][j];// 第一列只能从上到下
                } else {
                    int tmp = grid[i][j-1];
                    cout << "dp[0][j] = " << dp[0][j] << "; dp[1][j] = " << dp[1][j] << endl;
                    long long leftmax = max(dp[0][j-1]*grid[i][j-1], dp[1][j-1]*grid[i][j-1]);
                    long long updwmax = max(dp[0][j]*grid[i][j-1], dp[1][j]*grid[i][j-1]);
                    // 貌似进行空间优化之后是一样的形式呢，这么开心

                    // 更新最小值：
                    long long leftmin = min(dp[0][j-1]*grid[i][j-1], dp[1][j-1]*grid[i][j-1]);
                    long long updwmin = min(dp[0][j]*grid[i][j-1], dp[1][j]*grid[i][j-1]);
    //                dp[0][j] = leftmax % MODULO;
    //                dp[1][j] = leftmin % MODULO;
                    dp[0][j] = max(leftmax, updwmax) % MODULO;
                    dp[1][j] = min(leftmin, updwmin) % MODULO;
                }
            }
        }
        return (dp[0][cols] < 0)? -1: dp[0][cols];
    }
    
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> grid;
    
    grid = {{-1,-2,-3},{-2,-3,-3},{-3,-3,-2}};
    rtn = gua.maxProductPath(grid);
    std::cout << "expect value = -1, actual value = " << rtn << endl;
    
    grid = {{1,-2,1},{1,-2,1},{3,-4,1}};
    rtn = gua.maxProductPath(grid);
    std::cout << "expect value = 8, actual value = " << rtn << endl;

    grid = {{1,-1,0,-3,4,3,-3,3,-1,3,0,0,-4,2},{2,-2,-3,-4,0,-2,-3,3,1,4,1,-3,-1,-4},{-4,4,-4,-4,2,-4,3,0,-2,-4,3,4,-1,0},{-3,3,-4,-4,3,4,4,1,-1,-1,0,3,4,1},{1,3,-4,2,2,-3,1,-3,-4,-4,-1,-4,-4,4},{1,1,-1,1,-1,-1,3,-4,-1,2,-2,3,-4,0},{1,0,3,3,1,4,1,1,-4,-1,-3,4,-4,4},{4,3,2,3,0,-1,2,-4,1,0,0,1,3,4},{-4,4,-4,-4,2,-2,2,-1,0,-2,2,4,-2,-1},{-2,3,4,-4,3,3,-2,-1,0,-3,4,-2,-1,-4},{4,3,3,3,-3,1,2,-4,-1,4,-3,-3,2,0},{3,3,0,1,-4,-4,-3,3,-2,-4,2,4,-3,3},{-3,0,1,3,0,0,0,-4,-1,4,-1,-3,1,1},{-1,4,0,-3,1,-3,-1,2,1,-3,-1,-4,4,1}};
    rtn = gua.maxProductPath(grid);
    std::cout << "expect value = 31136867, actual value = " << rtn << endl;
    return 0;
}
