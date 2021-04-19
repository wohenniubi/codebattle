
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 80 ms, faster than 31.64%
    //Memory Usage: 36.9 MB, less than 18.70%
    int minCut(string s) {
        // 采用dp计算，dp[i]表示[0,i]位置的palindrome最少需要多少cut
        // 不过这个dp计算过程中又要用到一个另一个dp信息，所以得先算出来
        int size = s.size();
        
        vector<vector<int>> isParlin(size, vector<int>(size));
        // 初始化对角线上的val为1，因为自己就是palindrome
        for (int i = 0; i < size; ++i)
            isParlin[i][i] = 1;
        
        // 然后复习一下，从第i层向右上计算
        for (int len = 2; len <= size; ++len) {
            for (int i = 0; i <= size-len; ++i) {
                int j = i-1+len;
                // 考虑越界的问题
                if (len == 2) {
                    isParlin[i][j] = s[i]==s[j];
                } else {
                    isParlin[i][j] = (s[i]==s[j])? isParlin[i+1][j-1]: 0;
                }
            }
        }
        
        // 好啦，现在开始干正事
        vector<int> dp(size, size);
        // 表示[0,i]位置的substr需要最少多少cut，初始化为最大cut
        dp[0] = 0;
        
        for (int i = 1; i < size; ++i) {
            // 现在开始从头往i切切切; j初始值为0，每次不超过i
            for (int j = -1; j < i; ++j) {
                // 切成了两部分，[0,j]的数组和[j+1,i]的数组，其中前者刚好就是dp[j]
                // if (isParlin[j+1][i]) 大意了啊，越界了啊！！！
                if (isParlin[j+1][i])
                    //dp[i] = min(dp[i], dp[j]+1);// 只有剩下的部分是parlindrom，这么切才有意义
                    dp[i] = min(dp[i], (j==-1)?0:(dp[j]+1)); // j=-1表示完全是substr[0,i]
            }
        }
        return dp.back();
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string s;
    int rtn;
    rtn = gua.minCut(s = "aab");
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.minCut(s = "a");
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.minCut(s = "ab");
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}

