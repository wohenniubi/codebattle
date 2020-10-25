#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size();
    if (!rows) return 0;
    int cols = grid[0].size();
    if (!cols) return 0;

    vector<vector<int>> costs(rows,vector<int>(cols));
    costs[0][0] = grid[0][0];

    // 初始化第一行的所有列
    for (int j = 1; j < cols; ++j) {
      //costs[0][j] += grid[0][j];//大意啦大意啦！！
      costs[0][j] = costs[0][j-1] + grid[0][j];
    }
    // 初始化第一列的所有行
    for (int i = 1; i < rows; ++i) {
      //costs[i][0] += grid[i][0];//大意啦大意啦！！
      costs[i][0] = costs[i-1][0] + grid[i][0];
    }

    for (int i = 1; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        costs[i][j] = min(costs[i][j-1], costs[i-1][j]) + grid[i][j];
      }
    }
    return costs.back().back();
  }
};

int main() {
  Solution gua;
  int rtn;
  vector<vector<int>> grid;

  rtn = gua.minPathSum(grid={{1,3,1},{1,5,1},{4,2,1}});
  cout << "expect value = 7, actual value = " << rtn << endl;

  return 0;
}

