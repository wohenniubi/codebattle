
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 这样返回的是递增序列；注意放在solution里面时要设置为static
    static bool canFit(vector<int> &A, vector<int> &B) {
        // 这个函数没有问题，出问题的在增加子序列长度那里
        if (A[0] == B[0])
            return A[1] < B[1];
        return A[0] < B[0];
    }
    
    //Runtime: 1168 ms, faster than 36.65%
    //Memory Usage: 16.2 MB, less than 82.59%
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // 首先排个序，理论上greedy一下，只有整体递增才可能找到最长的子序列；有些题如果限制顺序不能改变，那么不能sort
        sort(envelopes.begin(), envelopes.end(), canFit);
        //cout << envelopes << endl;
        
        // 然后就是递增子序列的操作了，牢记此时的dp定义是以当前位置为结尾的最长子序列长度
        int size = envelopes.size();
        vector<int> dp = vector<int>(size,1);
        
        // 外层循环是子序列结尾的pos
        for (int i = 1; i < size; ++i) {
            // 内层循环是从i向左边遍历，寻找最长的子序列
            for (int j = i-1; j >= 0; --j) {
                if (envelopes[j][0] < envelopes[i][0]
                    && envelopes[j][1] < envelopes[i][1]) {
                //if (canFit(envelopes[j], envelopes[i])) { // 不能用排序的函数
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }
        return *max_element(begin(dp), end(dp));//dp[size-1]; 不要大意啊，这里的dp的定义不同，所以不是最后一个值
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<vector<int>> envelopes;

    rtn = gua.maxEnvelopes(envelopes={{10,8},{1,12},{6,15},{2,18}});
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    rtn = gua.maxEnvelopes(envelopes={{15,8},{2,20},{2,14},{4,17},{8,19},{8,9},{5,7},{11,19},{8,11},{13,11},{2,13},{11,19},{8,11},{13,11},{2,13},{11,19},{16,1},{18,13},{14,17},{18,19}});
    cout << "expect value = 5, actual value = " << rtn << endl;
    
    rtn = gua.maxEnvelopes(envelopes={{5,4}, {6,4}, {6,7}, {2, 3}});
    cout << "expect value = 3, actual value = " << rtn << endl;
    return 0;
}

