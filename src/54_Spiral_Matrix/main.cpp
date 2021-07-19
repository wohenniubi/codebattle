
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Runtime: 0 ms, faster than 100.00%
    // Memory Usage: 6.9 MB, less than 20.77%
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 据说是原型题，那么就把模版背下来吧
        vector<int> rtn;
        
        if (matrix.empty() || matrix[0].empty()) return rtn;
        
        int rowBgn = 0, rowEnd = matrix.size()-1;
        int colBgn = 0, colEnd = matrix[0].size()-1;
        
        while (rowBgn <= rowEnd && colBgn <= colEnd) {
            for (int i = colBgn; i <= colEnd; ++i)
                rtn.push_back(matrix[rowBgn][i]);
            ++rowBgn;// 减少了一行
            for (int i = rowBgn; i <= rowEnd; ++i)
                rtn.push_back(matrix[i][colEnd]);
            --colEnd;// 减少一列
            
            if (rowBgn > rowEnd) break;// 因为前面rowBgn发生了改变，而本次while轮回还没结束，因此需要增加这个判断
            for (int i = colEnd; i >= colBgn; --i)
                rtn.push_back(matrix[rowEnd][i]);
            --rowEnd;// 减少一行
            
            if (colBgn > colEnd) break;// 因为前面colEnd发生了改变，而本次while轮回还没结束，因此需要增加这个判断
            for (int i = rowEnd; i >= rowBgn; --i)
                rtn.push_back(matrix[i][colBgn]);
            ++colBgn;// 减少一列
        }
        
        return rtn;
    }

    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7 MB, less than 20.77%
    vector<int> spiralOrder1(vector<vector<int>>& matrix) {
        vector<int> rtn;
        if (matrix.empty()) return rtn;
        
        int top = 0, dwn = matrix.size();// 0, 3
        int lhs = 0, rhs = matrix[0].size();// 0, 3
        // int lhs = -1, rhs = matrix[0].size(); //写成-1，才能满足凑出一个子问题
        
        while (top < dwn && lhs < rhs) {
            // 先从左到右;
            for (int x = top, y = lhs; y < rhs; ++y) {
                rtn.push_back(matrix[x][y]);
            }
            ++top;// 顶部少一行
            
            // 再从上到下
            for (int x = top, y = rhs-1; x < dwn; ++x) {
                rtn.push_back(matrix[x][y]);
            }
            --rhs;//右侧少一列
           
            // 大意了大意了，这里还需要增加行的判断，在跑case的时候发现的问题
            if (top >= dwn) break;// 由于top发生了改变，这里不跳出的话，剩下的两个方向可能出现重复

            // 再从右到左
            for (int x = dwn-1, y = rhs-1; y >= lhs; --y) {
                rtn.push_back(matrix[x][y]);
            }
            --dwn;// 底层少一行
           
            if (lhs >= rhs) break;// 这里也类似，由于rhs在先前发生了变化，所以要加赠判断

            // 再从下到上
            for (int x = dwn-1, y = lhs; x >= top; --x) {
                rtn.push_back(matrix[x][y]);
            }
            ++lhs;// 左侧少一列，然后循环到while开始的地方，看看从左到右是否满足
        }
        
        return rtn;
    }
};

ostream &operator<<(ostream &os, vector<int> &rtn) {
  os << "[";
  for (auto val : rtn) 
    os << val << ", ";
  os << "]";
  return os;
}

int main() {
  Solution gua;
  vector<vector<int>> matrix;
  vector<int> rtn;

  rtn = gua.spiralOrder(matrix = {{7},{9},{6}});
  cout << rtn << endl;
  
  rtn = gua.spiralOrder(matrix = {{1,2,3},{4,5,6},{7,8,9}});
  cout << rtn << endl;
  
  rtn = gua.spiralOrder(matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}});
  cout << rtn << endl;
  return 0;
}

