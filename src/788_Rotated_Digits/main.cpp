
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 48.59% 
    //Memory Usage: 7 MB, less than 12.87%
    // 方法2: 在1的基础上非常巧妙的dp方法，dp[n]表示n这个数的状态
    // 0表示旋转后invalid的数，1是valid的数，2是good的数，那么dp[n]的状态是由dp[n/10]和dp[n%10]来决定的
    int rotatedDigits(int n) {
        int rtn = 0;
        vector<int> dp(n+1);// 记录从1到n的数字，初始化为0，没毛病
        
        //dp[1] = 1;
        // 大意了，还需要把个位全部初始化一遍，但是下面的方式会导致n=1时越界，所以还是放在for循环里安全些
        //dp[0] = 1; dp[2] = 2; dp[5] = 2; dp[6] = 2; dp[8]= 1; dp[9] = 2;
        
        // dp[n]的状态是由dp[n/10]和dp[n%10]来决定的，因为每个digit是独自旋转的，否则不能这么做
        for (int i = 0; i <= n; ++i) {
            if (i < 10) {
                if (i == 0 || i == 1 || i == 8) {
                    dp[i] = 1;
                } else if (i != 3 && i != 4 && i != 7) {
                    dp[i] = 2;
                    ++rtn;// 别忘了++
                }
                continue;
            }
            
            // 这里用乘法，与0，1，2的意义比较好的联系在一起：
            // 如果两部分中任意一部分为循环invalid，即等于0，那么整体为0，
            // 如果两部分都是valid，那么整体还是valid的；
            // 如果存在任意一部分为good，那么整体为good，但是要让值为2，因为可能是2或者4
            dp[i] = dp[i/10] * dp[i%10];
            if (dp[i] >= 2) {
                dp[i] = 2;
                ++rtn;
            }
        }
        
        return rtn;
    }
    
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6 MB, less than 50.37%
    // 方法1: 从1到n，每个数按照digit进行检查，时间复杂度O(5n)，因为n最大是10000，所以最多5位
    int rotatedDigits1(int n) {
        int rtn = 0;
        for (int i = 1; i <= n; ++i) {
            //if (isNumGood(n)) 怎么如此大意！！
            if (isNumGood(i))
                ++rtn;
        }
        return rtn;
    }
    
    bool isNumGood(int n) {
        // 7个数字, 0,1,2,5,6,8,9旋转后是valid的，
        // 在其中仅有2, 5, 6, 9是good
        bool rtn = false;
        
        // 思路是判断每一个digit，如果出现了旋转后invalid的数，直接返回false
        // 至少要存在一个good digit，否则的话旋转完了不能产生不同的数
        while (n) {
            int digit = n % 10;
            if (digit == 3 || digit == 4 || digit == 7)
                return false;// 只要存在invalid的digit，就不用算了
            
            if (digit == 2 || digit == 5 || digit == 6 || digit == 9)
                rtn = true;// 还是需要继续检查，防止后面出现invalid
            
            n /= 10;
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, n;

    rtn = gua.rotatedDigits(n = 857);
    cout << "expect value = 247, actual value = " << rtn << endl;

    rtn = gua.rotatedDigits(n = 1);
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.rotatedDigits(n = 10);
    cout << "expect value = 4, actual value = " << rtn << endl;
    return 0;
}
