#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 经典的动态规划题目: 要建立二维DP数组dp[i][j]
    // 关键是dp中i和j的意义, i和j分别代表text1中0~i这段substr1和text2中0~j这段substr2
    // dp[i][j]代表的是substr1和substr2的最长common string
    // 这里的subsequence其实提示了可以用for loop来解决, 
    // 因为for loop是依次遍历index的, 这就保证了次序
    // Runtime: 36 ms, faster than 26.67%
    // Memory Usage: 13.2 MB, less than 5.54%
    int longestCommonSubsequence(string text1, string text2) {
        int rtn, len1 = text1.size(), len2 = text2.size();
        // 然后dp数组的更新条件是:
        // 如果text1[i]与text2[j]相等, 那么dp[i][j]就等于dp[i-1][j-1] + 1
        // 如果text1[i]与text2[j]不等, 那么dp[i][j]就等于dp[i-1][j]或者dp[i][j-1]
        // 中的较大者, 这等价于用稍微短一个长度的text1’或者text2‘与另一个text进行比较

        // 有个小trick, 由于dp的更新条件出现了i-1和j-1, 所以为了避免逻辑判断让代码简洁
        // 初始化dp时为text1和text2都多申请一个, 就可以巧妙处理边界情况, 只需注意index
        // vector的默认值等于0, 所以正好
        vector<vector<int>> dp(len1+1, vector<int>(len2+1));

        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                // 稍微注意一下i和j到text1和text2的index映射
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[len1][len2];
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    string text1, text2;
    int rtn;
    rtn = gua.longestCommonSubsequence(text1 = "abcde", text2 = "ace");
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.longestCommonSubsequence(text1 = "abc", text2 = "def");
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}
