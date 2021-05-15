
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 解法1: 有点像一维数组从左看，从右看到当前位置的值
    // 这里是二维数组从左右看，上下看到当前位置的值
    // Runtime: 40 ms, faster than 58.31%
    // Memory Usage: 15.7 MB, less than 10.17%
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int row = grid.size(), col = grid[0].size();
        vector<vector<int>> lTocur(row,vector<int>(col)), rTocur=lTocur, uTocur=lTocur, dTocur=lTocur;
    
        for (int i = 0; i < row; ++i) {
            // 从左往右，从右往左
            lTocur[i][0] = (grid[i][0]=='E')?1:0;//相当于[i][-1]有墙
            for (int j = 1; j < col; ++j) {
                lTocur[i][j] = (grid[i][j]=='E')?lTocur[i][j-1]+1:
                        (grid[i][j]=='0')?lTocur[i][j-1]: 0;
            }
            rTocur[i][col-1] = (grid[i][col-1]=='E')?1:0;
            for (int j = col-2; j >= 0; --j) {
                rTocur[i][j] = (grid[i][j]=='E')?rTocur[i][j+1]+1:
                        (grid[i][j]=='0')?rTocur[i][j+1]: 0;
            }
        }
        
        for (int j = 0; j < col; ++j) {
            // 从上往下，从下往上
            uTocur[0][j] = (grid[0][j] == 'E')?1:0;
            for (int i = 1; i < row; ++i) {
                uTocur[i][j] = (grid[i][j]=='E')?uTocur[i-1][j]+1:
                        (grid[i][j]=='0')?uTocur[i-1][j]:0;
            }
            dTocur[row-1][j] = (grid[row-1][j] =='E')?1:0;
            for (int i = row-2; i >=0; --i) {
                dTocur[i][j] = (grid[i][j]=='E')?dTocur[i+1][j]+1:
                        (grid[i][j]=='0')?dTocur[i+1][j]:0;
            }
        }
        
        // 好啦，终于把历史信息写好了，开干吧
        int rtn = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] != '0') continue;
                int sum = lTocur[i][j] + rTocur[i][j] + uTocur[i][j] + dTocur[i][j];
                rtn = max(rtn, sum);
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<char>> grid;
    rtn = gua.maxKilledEnemies(grid={{'0','E','0','0'},{'E','0','W','E'},{'0','E','0','0'}});
    cout << "expect value = 3, actual value = " << rtn << endl;
    
    return 0;
}
