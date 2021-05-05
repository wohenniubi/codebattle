
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 是典型的回溯问题
    //Runtime: 12 ms, faster than 91.82%
    //Memory Usage: 9 MB, less than 70.44%
    bool backtrack(string &pattern, unordered_map<string,bool> &memo) {
        // 返回条件TODO,貌似不需要呀
        if (memo.count(pattern))
            return memo[pattern];
        
        // 从第二位开始，每次回一位，每个人都按照自己的最优来操作，要把所有位置试一下
        bool rtn = false;
        for (int i = 1; i < pattern.size(); ++i) {
            if (pattern[i-1] == '+' && pattern[i] == '+') {
                pattern[i-1]= '-'; pattern[i] = '-';
                
                bool tmp = backtrack(pattern, memo);// 看对方是不是会赢，
                pattern[i-1]= '+'; pattern[i] = '+';
                // 每个人都在minMax，由于这里是bool，因此max最好也就是1表示赢，
                if (!tmp) {
                    //说明把pattern[i-1]和pattern[i]设置为'-'的操作可以让对方失败，那么就按照这个套路
                    rtn = true;
                    break;
                }
            }
        }
        // 如果没有让rtn变为true，说明每个操作对手都可以赢，或者自己都无从下手，那么就是输；记录自己在给定pattern时的输赢情况
        return memo[pattern] = rtn;
    }
    
    bool canWin(string currentState) {
        // bool rtn = false;
        if (currentState.size() < 2)
            return false;
        
        unordered_map<string,bool> memo;
        return backtrack(currentState, memo);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    string pattern;
    
    rtn = gua.canWin(pattern="++++");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canWin(pattern="+");
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}
