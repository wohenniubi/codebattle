
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 16 ms, faster than 23.26%
    //Memory Usage: 8.1 MB, less than 74.56%
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        // 硬算吧, mat1 = m*k, mat2 = k*n
        int row = mat1.size(), col = mat2[0].size();
        vector<vector<int>> rtn = vector<vector<int>>(row,vector<int>(col));

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int sum = 0;
                for (int k = 0; k < mat1[i].size(); ++k) {
                    sum += mat1[i][k] * mat2[k][j];
                }
                rtn[i][j] = sum;// 设置值到rtn[i][j];
            }
        }
        return rtn;
    }
};

ostream &operator<<(ostream &os, vector<vector<int>> &rtn) {
  os << "{";
  for (auto & row : rtn) {
    os << "{";
    for (auto & col : row) {
      os << col << ", ";
    }
    os << "},";
  }
  os << "}";
  return os;
}

int main() {
  Solution gua;
  vector<vector<int>> rtn, mat1, mat2;
  rtn = gua.multiply(mat1 = {{1,0,0},{-1,0,3}}, mat2={{7,0,0},{0,0,0},{0,0,1}});
  cout << "expect value = {{7,0,0}, {-7,0,3}}, actual value = " << rtn << endl;

  rtn = gua.multiply(mat1 = {{0}}, mat2={{0}});
  cout << "expect value = {{0}}, actual value = " << rtn << endl;

  return 0;
}

