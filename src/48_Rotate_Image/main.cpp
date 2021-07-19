
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 61.23%
    //Memory Usage: 6.9 MB, less than 92.60%
    void rotate(vector<vector<int>>& matrix) {
        // 向右旋转90度，那不就是左右翻转后右对角线翻转吗
        int n = matrix.size();
        
        // 右对角线翻转m[i][j] <-> m[j][i]
        for (int i = 0; i < n; ++i) {
            //for (int j = 0; j < i; ++j) { // 大意了，不是j<i和swap[i][j], [j][i]),这样是左对角线翻转
            for (int j = i; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // 每一行里面左右翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n/2; ++j) {
                swap(matrix[i][j], matrix[i][n-j-1]);
            }
        }
        return;
    }
};

ostream & operator<<(ostream &os, vector<vector<int>> &matrix) {
    os << "[";
    for (auto &row : matrix) {
        os << "[";
        for (auto val : row) {
            os << val << ", ";
        }
        os << "]" << endl;
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<int>> matrix;
    gua.rotate(matrix = {{1,2,3},{4,5,6},{7,8,9}});
    cout << matrix << endl;
    
    gua.rotate(matrix = {{1}});
    cout << matrix << endl;
    
    gua.rotate(matrix = {{1,2},{3,4}});
    cout << matrix << endl;
    return 0;
}
