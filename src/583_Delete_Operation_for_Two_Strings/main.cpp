#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Runtime: 28 ms, faster than 49.88%
    // Memory Usage: 12.4 MB, less than 9.32% 
    int minDistance(string word1, string word2) {
        // 想到一个与该题最相近的题, 最长common sequence
        // 字符长度不超过500, dp解法, 时间复杂度O(n^2) 应该还ok
        int len1 = word1.size(), len2 = word2.size();
        vector<vector<int>> dp(len1+1, vector<int>(len2+1));
        
        //for (int i = 1; i < len1; ++i) {
        //    for (int j = 1; j < len2; ++j) { 大意啦大意啦，边界条件！！
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    // 如果两个char相同; 那么就是更短的word1'和word2'的比较
                    dp[i][j] = max(dp[i-1][j-1]+1, dp[i][j]);
                } else {
                    // 如果两个char不相同; 那么就是更短的word1'和word2, 
                    // 或者word1与更短的word2'的比较
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        // 最后dp[len1][len2] 就是最长公共子序列
        return len1 + len2 - 2*dp.back().back();
    }
};

int main() {
  Solution gua;
  int rtn;
  string word1, word2;

  rtn = gua.minDistance(word1="sea", word2="eat");
  cout << "expect value = 2, actual value = " << rtn << endl;
  return 0;
}


