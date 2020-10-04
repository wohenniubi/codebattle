//
//  main.cpp
//  416_Partition_Equal_Subset_Sum
//
//  Created by Jiafan Wang on 9/24/20.
//

#include <iostream>
#include <vector>

using namespace std;

//Runtime: 184 ms, faster than 46.25%
//Memory Usage: 9.6 MB, less than 61.92%
//这是0/1 背包问题的变种，一次通过且空间优化，赞！
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto & num : nums) sum+= num;
        
        if (sum%2) return false;// 说明不能拆成两个相等的subset
        sum /= 2;// 这是背包的体积
        vector<int> dp(sum+1);
        for (auto & num : nums) {
            for (int i = sum; i > 0; --i) {
                if (i >= num) {
                    dp[i] = max(dp[i-num]+num, dp[i]);
                } else {
                    dp[i] = dp[i];
                }
            }
        }
        return dp.back() == sum;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> nums;
    rtn = gua.canPartition(nums = {1,5,11,5});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.canPartition(nums = {1,2,3,5});
    cout << "expect value = 0, actual value = " << rtn << endl;
    return 0;
}
