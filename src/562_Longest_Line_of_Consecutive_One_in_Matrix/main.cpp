#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 一定是采用dp算法，不过具体方式有两种，第一种是四个方向遍历，每次更新一种情况的最长连续1
    // 第二种是用一个三维数组dp[i][j][k]，其中i和j是行列，k表示行、列、左对角线、右对角线的最长到目前为止的最长连续1
    //Runtime: 132 ms, faster than 15.43% 
    //Memory Usage: 44.5 MB, less than 9.61%
    int longestLine(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n,vector<int>(4)));// 三维dp数组，保存到[i][j]位置的最长1
        int rtn = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) continue;// 如果是0就跳过
                
                // 如果是1，则更新水平，垂直，左斜和右斜的最长1
                dp[i][j] = vector<int>(4,1);//非常巧妙
                if (j>0) dp[i][j][0] += dp[i][j-1][0];//水平更新
                if (i>0) dp[i][j][1] += dp[i-1][j][1];//垂直更新
                if (i>0 && j>0) dp[i][j][2] += dp[i-1][j-1][2];
                if (i>0 && j<n-1) dp[i][j][3] += dp[i-1][j+1][3];
                
                rtn = max(rtn, max(dp[i][j][0], dp[i][j][1]));
                rtn = max(rtn, max(dp[i][j][2], dp[i][j][3]));
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> mat;
    
    rtn = gua.longestLine(mat = {{0,1,1,0}, {0,1,1,0}, {0,0,0,1}});
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.longestLine(mat = {{1,1,0,0}, {0,1,1,0}, {0,0,0,1}});
    cout << "expect value = 3, actual value = " << rtn << endl;
    return 0;
}

