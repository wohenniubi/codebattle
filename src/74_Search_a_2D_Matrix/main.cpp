
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 9.6 MB, less than 48.83%
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        
        int m = matrix.size(), n = matrix[0].size();
        int lhs = 0, rhs = m*n-1;
        
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            int x = mid/n, y = mid%n;
            if (matrix[x][y] == target)
                return true;// mid处理结束
            
            if (matrix[x][y] > target) {
                rhs = mid-1;
            } else {
                lhs = mid+1;
            }
        }
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int target;
    vector<vector<int>> matrix;
    
    rtn = gua.searchMatrix(matrix = {{1,3,5,7}, {10,11,16,20}, {23,30,34,60}}, target = 3);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.searchMatrix(matrix = {{1,3,5,7}, {10,11,16,20}, {23,30,34,60}}, target = 4);
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}
