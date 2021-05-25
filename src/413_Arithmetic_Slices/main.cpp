
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 6.47%
    //Memory Usage: 7.4 MB, less than 49.92%
    int numberOfArithmeticSlices(vector<int>& A) {
        // 稍微优化一下，把dp[i][i+1] = dp[i-1][i] + 1;这里的dp[i][i+1]和dp[i-1][i]整个当作2个变量，同时注意要完善else的操作
        int size = A.size(), rtn = 0;
        
        int val = 0;
        for (int i = 1; i < size-1; ++i) {
            if (2*A[i] == A[i-1] + A[i+1]) {
                val = val + 1;
            } else {
                val = 0;// 在有dp数组的情况下，这个else不用写，因为使用的dp值事先进行了初始化，为0
            }
            rtn += val;
        }
        return rtn;
    }
    
    // Runtime: 28 ms, faster than 5.22%
    // Memory Usage: 148.9 MB, less than 5.43%
    int numberOfArithmeticSlices1(vector<int>& A) {
        // 这里是subarray，不能随意截取sequence A，因此arithmetic array的个数要少一些，问题也要简单一些
        int size = A.size();
        
        // 然后使用dp数组来存结果
        //这里dp[i][j]表示的是以A[i]和A[j]作为arithmetic数列最后两个数的序列（len>=3）的个数，初始化为0没毛病
        vector<vector<int>> dp(size,vector<int>(size));// 实际只使用了右上部分的空间，因为i < j
        
        int rtn = 0;
        for (int i = 1; i < size-1; ++i) {
            // 因为是subarray，所以不能跳跃取数据，只能是i-1, i, i+1，所以貌似不需要用内循环
            if (A[i-1] + A[i+1] == 2*A[i]) {
                dp[i][i+1] = dp[i-1][i] + 1;
                // 两部分：1）dp[i-1][i]包含的所有序列后面增加一个A[i+1]，这部分等于dp[i-1][i]
                // 2）A[i-1]和A[i]原本是不满足三个数的限制，现在加上A[i+1]，成为一个新的序列，因此加1
            }
            rtn += dp[i][i+1];
            //for (int j = i+1; j < size; ++j) {
            // 肯定不能和i相同，否则就只有一个数
            // }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> A;
    rtn = gua.numberOfArithmeticSlices(A={1,2,3,4});
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.numberOfArithmeticSlices(A={1,2});
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}
