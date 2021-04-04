
#include <iostream>
#include <unordered_map>

using  namespace std;

class Solution {
public:
    //Runtime: 532 ms, faster than 10.65%
    //Memory Usage: 29.5 MB, less than 32.95%
    int superEggDrop(int k, int n) {
        unordered_map<string, int> memo;
        return dp(k, n, memo);
    }

    int dp(int k, int n, unordered_map<string, int> &memo) {
        // 返回条件
        if (k == 1) return n; // 只有1个蛋，老老实实扔吧
        if (n <= 1) return n; // 楼层为1或者0，分别扔1次或0次
        
        string key = to_string(k) + '#' + to_string(n);
        if (memo.count(key)) return memo[key];
        int rtn = INT_MAX;
        // for (int i = 1; i <= n; ++i) {
        //     rtn = min(rtn, 1 + max(dp(k-1, i-1, memo), dp(k, n-i, memo)));// 分别为破与不破两种情况，然后选所有最坏情况中最的
        int lhs = 1, rhs = n;
        while (lhs <= rhs) {
            int mid = lhs + (rhs-lhs)/2;//mid表示扔鸡蛋的楼数
            int eggfail = dp(k-1, mid-1, memo);// 这是基于mid的单调增函数
            int egggood = dp(k, n-mid, memo);//这是基于mid的单调减函数
            // rtn = 1 + min(max(eggfail, egggood));
            rtn = 1 + min(rtn, max(eggfail, egggood));
            if (eggfail > egggood) {
                rhs = mid-1;// 说明mid在最值右边
            } else if (eggfail < egggood) {
                lhs = mid+1;// 说明mid在最值左边
            } else {
                break; // 相等了不就是所得吗
            }
        }
        
        return memo[key] = rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, k, n;
    rtn = gua.superEggDrop(k=1, n=2);
    cout << "expect value = 2, actual value = " << rtn << endl;
    
    rtn = gua.superEggDrop(k=2, n=6);
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.superEggDrop(k=3, n=14);
    cout << "expect value = 4, actual value = " << rtn << endl;
    
    return 0;
}
