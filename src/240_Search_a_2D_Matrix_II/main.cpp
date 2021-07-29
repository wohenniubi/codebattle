
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 100 ms, faster than 76.79% 
    //Memory Usage: 14.9 MB, less than 65.69%
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // if (matrix.empty() || matrix[0].emtpy()) return false;
        if (matrix.empty() || matrix[0].empty()) return false;
        
        // 有点二分法的意思，找到某个值，可以判断迭代的方向
        int m = matrix.size(), n = matrix[0].size();
        int row = 0, col = n-1;// 相当于右上角为mid
        
        // while (row < m && col > 0) { //怎么这么大意
        while (row < m && col >= 0) {
            if (matrix[row][col] == target)
                return true;
            
            if (matrix[row][col] > target) {
                // 那么去掉当前列，因为这一列都比target大
                --col;
            } else {
                // 那么肯定在下一行，因为这一行都比target小
                ++row;
            }
        }
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<vector<int>> matrix;
    int target;
    
    rtn = gua.searchMatrix(matrix={{-5}}, target = -5);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.searchMatrix(matrix={{1,4,7,11,15}, {2,5,8,12,19}, {3,6,9,16,22}, {10,13,14,17,24}}, target = 5);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.searchMatrix(matrix={{1,4,7,11,15}, {2,5,8,12,19}, {3,6,9,16,22}, {10,13,14,17,24}}, target = 20);
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}
