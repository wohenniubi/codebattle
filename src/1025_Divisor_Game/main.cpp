#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    bool divisorGame(int N) {
        // 能想到就是递归 + memo； 每个子问题返回的是必定为true或者为false的情况
        // 在都遵循最优操作的前提下，Alice和Bob的操作本质都是一样的，A赢就是B输
        // 所以没有必要再为递归函数增加flag
        
        //初始化为-1是有目的的，-1表示还没有赋值；1和0分别表示赢和输，这样可以直接传递给bool
        memo = vector<int>(N+1,-1);
        return helper(N);
    }

    // 首先要明白谁先到N=2谁赢，奇数的因数肯定都是奇数，偶数的因数有奇数和偶数，
    // 由于最优策略，最后肯定是到N=2的。如果N是偶数，Alice只要选奇数，不行就一直选1，
    // 那么最后N=2的时候肯定是Alice赢，相反的假如N是奇数，因数也是奇数，那么到鲍勃N就是偶数，
    // 那么Alice肯定输。所以最后只需要判断奇偶就行了
    bool divisorGame2(int N) {
        return N%2 == 0;// 没有看懂数学推导，要是能在短时间想到这一点也太牛了
    }
    
private:
    // 存的是给定N的时候，当前选择的人会不会赢 (不要想flipflop反转)
    vector<int> memo;
    
    // 下面就是常规的写法，recursive+memo
//    Runtime: 4 ms, faster than 34.04%
//    Memory Usage: 6.3 MB, less than 8.94%
    bool helper(int N) {
        if (N == 1) return false;
        
        if (memo[N] != -1) return memo[N];
        
        bool rtn = 0;
        for (int x = 1; x < N; ++x) {
            if (N%x == 0) {
                // 注意这里之所以要取反，是因为我们希望对方输，只要对方输一次，
                // 就朝着让对方输的这个move挺进，貌似没有必要把所有的情况都过一遍
                rtn |= !helper(N-x);
                if (rtn) break;
            }
        }
        return memo[N] = rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int N;
    rtn = gua.divisorGame(N=2);
    std::cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.divisorGame(N=3);
    std::cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.divisorGame(N=4);
    std::cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}

