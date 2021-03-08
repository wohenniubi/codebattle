
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.9 MB, less than 47.49%
    bool canWinNim(int n) {
        if (n > 128) {
            return n%4;
        }
        // 我就想试一试dp的做法
        if (n <= 3) return true;
        // if (n == 4) return false; 貌似4可以融合到下面的for循环里面
        
        vector<bool> dict(n+1); //这里dict存的是自己在给定n的情况下是否可以赢，赢为1，输为0
        dict[1] = dict[2] = dict[3] = 1;
        // dict[4] = 0;
        // for (int i = 4; i <= 128; ++i) { 大意啦，到n不是128
        for (int i = 4; i <= n; ++i) {
            // 查找前一次的结果（即对方的情况，由于大家都是以最优的策略来操作，所以自己的信息也可以用作对方的信息）
            bool canWin = false;
            for (int j = 1; j <= 3; ++j) {
                // 看是否存在某种情况，使得对方在自己取走j个石头之后输掉
                if (dict[i-j] == 0) {
                    canWin = true;
                    break;
                }
            }
            // for循环结束可能是跳出的，那样canWin=true
            // 也可能是执行完3种选择之后都没有对方都没有输掉，那样canWin=false
            dict[i] = canWin;
        }
        return dict[n];
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int n;
    rtn = gua.canWinNim(n = 8);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.canWinNim(n = 9);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canWinNim(n = 4);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.canWinNim(n = 3);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canWinNim(n = 5);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
