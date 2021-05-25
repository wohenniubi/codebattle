
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 896 ms, faster than 13.92% 
    //Memory Usage: 89.4 MB, less than 19.66%
    // 这里remSum是totalSum和desiredTotal的差值，当小于等于0时，说明上一个选手完成了desiredTotal
    // 因为visit和remSum是int了，所以不需要用reference，这样可以减少add/del的操作
    bool minMaxWin(int visit, int remSum, int maxInteger, unordered_map<int,bool> &memo) {
        // TODO: 返回条件
        if (remSum <= 0) return false;// 说明当前选手失败，上一轮的选手成功
        // if (totalSum >= desiredTotal)
        //     return true;
        
        // 当前选手是否可以在当前剩余visit的情况下达到目标值
        if (memo.count(visit))
            return memo[visit];
        
        // 现在遍历所有可以用的integer
        bool rtn = false;
        for (int i = 0; i < maxInteger; ++i) {
            if (0 == ((1<<i) & visit)) continue;

            // visit &= ~(1<<i);
            // totalSum -= (i+1);//这里bit的位置就对应integer的值
            
            // minMax就是要找最好的情况里面的最差的情况，对于返回bool输赢，那么最好的情况就是对方为false
            // 只要对方有一种情况是输的，那么我就是赢的，
            if (!minMaxWin(visit & ~(1<<i), remSum - (i+1), maxInteger, memo)) {
                rtn = true;
                break;// 说明有一种选择会让对方失败，那么就选择这个选择
            }
        }
        //return isA && ~rtn:
        //return !rtn;貌似与isA没有啥关系了
        memo[visit] = rtn;
        return rtn;
    }
    
    // 看了答案，还是使用的memo+backtrack的做法，然后每次进行minMax的操作
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        // 为了应对maxChoosableInteger = 10, desiredTotal = 0的情况
        if (desiredTotal <= 0) return true;
        // 为了应对maxChoosableInteger = 5, desiredTotal = 50的情况，即使全部数都加上，双方都无法达到目标
        if ((maxChoosableInteger+1)*maxChoosableInteger/2 < desiredTotal) return false;
        
        // 老样子，A B两个人各自都会进行min-max都操作，即选择最好的情况
        int n = maxChoosableInteger;
        int visit = (1<<n)-1;// 这个visit其实起到了path的作用
        
        // 然后子问题的状态有，当前剩余可选的数，与desiredTotal相比当前剩余的值，当前是A还是B
        // return minMaxWin(visit, totalSum, desiredTotal, maxChoosableInteger, true);
        unordered_map<int,bool> memo;//这里也可以用vector来保存(1<<n)个数
        return minMaxWin(visit, desiredTotal, maxChoosableInteger, memo);
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int maxChoosableInteger, desiredTotal;

    rtn = gua.canIWin(maxChoosableInteger = 5, desiredTotal = 0);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canIWin(maxChoosableInteger = 5, desiredTotal = 50);
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}
