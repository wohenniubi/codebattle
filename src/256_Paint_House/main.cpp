#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    #define RED 0
    #define BLUE 1
    #define GREEN 2
    //Runtime: 12 ms, faster than 95.47%
    //Memory Usage: 9.8 MB, less than 5.52%
    int minCost(vector<vector<int>>& costs) {
        int num = costs.size();

        // 完全背包问题 + 空间压缩
        if (!num) return 0;
        // int red = blue = green = 0; 编译错误，大意啦
        int red, blue, green;
        red = blue = green = 0;

        for (int i = 0; i < num; ++i) {
            // red[i] = min(blue[i-1], green[i-1]) + costs[i][RED];
            // blue[i] = min(red[i-1], green[i-1]) + costs[i][BLUE];
            // green[i] = min(red[i-1], blue[i-1]) + costs[i][GREEN];
            int old_red = red, old_blue = blue;
            red = min(old_blue, green) + costs[i][RED];
            blue = min(old_red, green) + costs[i][BLUE];
            green = min(old_red, old_blue) + costs[i][GREEN];
        }
        return min(red, min(blue, green));
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<vector<int>> costs;

  rtn = gua.minCost(costs={{17,2,17},{16,16,5},{14,3,19}});
  cout << "expect value = 10, actual value = " << rtn << endl;

  return 0;
}


