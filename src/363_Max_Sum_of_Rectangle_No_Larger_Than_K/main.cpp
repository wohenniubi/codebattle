
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    // 方法2：在方法1的基础上用到了用到了二分查找的思路，寻找一维数组的subarray值小于等于k
    // 外部for循环也很巧妙，将二维数组巧妙分解为一维数组
    //Runtime: 988 ms, faster than 11.35%
    //Memory Usage: 131.3 MB, less than 26.26%
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (!matrix.size()) return 0;
        
        int row = matrix.size(), col = matrix[0].size();
        int rtn = INT_MIN;
        
        for (int i = 0; i < col; ++i) {
            vector<int> sum(row);// matrix[*][i]

            // 内外这两个for循环，遍历了以matrix[*][i]为左边界，matrix[*][j]为右边界的子矩阵区间
            for (int j = i; j < col; ++j) {
                
                // 在该区间内，可以通过映射将二维的矩阵的sum，压缩为一维array的sum
                for (int k = 0; k < row; ++k) {
                    sum[k] += matrix[k][j];
                }
                
                // 此时可以利用一维数组的prefix sum查找，确定是否存在某个subarray的sum小于等于k
                set<int> helper{{0}};// 先存个0，因为要查找curSum -k的值
                int curSum = 0;
                //for (int k = 0; k < row; ++k) { 不要和输入弄成一样的
                for (int p = 0; p < row; ++p) {
                    curSum += sum[p];
                    auto iter = lower_bound(helper.begin(), helper.end(), curSum - k);
                    // 如果找到 Ans >=(curSum -k)，说明k >= curSum - Ans，这就是所求
                    if (iter != helper.end()) {
                        rtn = max(rtn, curSum - *iter);
                    }
                    helper.insert(curSum);// 把当前值存入，可以便于后续查找
                }
            }
        }
        
        return rtn;
    }
    
    // 方法1：时间复杂度O(m^2n^2)，有一个leetcode的题超时，不过可以作为一个基础解法
    int maxSumSubmatrix1(vector<vector<int>>& matrix, int k) {
        // 先试试brute force方法吧，尽管借助了前缀和，复杂度还是很高O(n*n*n*m)
        int row = matrix.size();
        if (!row) return 0;
        int col = matrix[0].size();
        
        // sum的定义为左上角为matrix[0][0]，右下角为matrix[i][j]的子矩阵的sum
        vector<vector<int>> sum = matrix;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (i>0) sum[i][j] += sum[i-1][j];
                if (j>0) sum[i][j] += sum[i][j-1];
                // sum[i-1][j-1]是交集部分，加多了，要减去
                if (i>0 && j>0) sum[i][j] -= sum[i-1][j-1];
            }
        }
        
        int rtn = INT_MIN;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                // 现在暴力求解matrix[0][0]到matrix[i][j]这部分数字中存在的、包含matrix[i][j]的新矩阵
                for (int p = 0; p <= i; ++p) {
                    for (int q = 0; q <= j; ++q) {
                        int tmp = sum[i][j];
                        if (p>0) tmp -= sum[p-1][j];
                        if (q>0) tmp -= sum[i][q-1];
                        // 减多了，要把交集部分加回来
                        if (p>0 && q>0) tmp += sum[p-1][q-1];
                        if (tmp <= k)
                            rtn = max(rtn, tmp);
                    }
                }
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, k;
    vector<vector<int>> matrix;
    rtn = gua.maxSumSubmatrix(matrix = {{1,0,1},{0,-2,3}}, k = 2);
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.maxSumSubmatrix(matrix = {{2,2,1}}, k = 3);
    cout << "expect value = 3, actual value = " << rtn << endl;

    return 0;
}
