
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //Runtime: 80 ms, faster than 98.44%
    //Memory Usage: 29.5 MB, less than 94.06%
    int numberOfArithmeticSlices(vector<int>& nums) {
        // 非常鸡贼的dp做法，以最后两个数作为sequence的结尾，那么来吧
        int size = nums.size(), rtn = 0;
        vector<vector<int>> dp(size,vector<int>(size));// 初始化为0说得通
        unordered_map<long, vector<int>> helper;// 保存每个出现的数的index
        for (int i = 0; i < nums.size(); ++i)
            helper[nums[i]].push_back(i);
        
        // 这里只用到这个2D矩阵的上半部分，i小于等于j
        // dp[i][j]表示以nums[i]和nums[j]作为序列最后两个数时的arithmetic序列个数
        for (int i = 0; i < size; ++i) {
            for (int j = i+1; j < size; ++j) {
                // 此时要更新dp[i][j]的值了，它的更新很有意思：因为等差数列至少长为3，
                // 因此需要找到target，使得target,nums[i],nums[j]等差
                // 这样就可以由dp[index(target)][i]+1得到dp[i][j]，之所以要加1
                // 是因为除了在target,nums[i]这两个数组成的等差数列最后补上nums[j] -- 这是等于
                // 还可以组成target,nums[i],nums[j]这1个新数组，它不包含在dp[index(target)][i]中
                // 因为dp[index(target)][i]的等差数列长度至少为3, 仅仅target,nums[i]的话长度为2
                
                // 不过问题又来了，target可以由2*nums[i]-nums[j]得到，但是如何获得target的index
                // 没办法，只好先把target的index保存下来到一个哈希表，然后这里逐一遍历
                // int target = 2*nums[i] +nums[i];// 小心越界哟
                // long target = 2*((long)nums[i]) +nums[i];// 怎么这么大意！！！
                long target = 2*((long)nums[i]) - nums[j];
                auto iter = helper.find(target);
                if (iter == helper.end()) continue;// 没有值可以组成等差数列
                for (auto pos : iter->second) {
                    if (pos >= i) continue;// 要小于i才是有效的序列成员
                    //这是以nums[pos],nums[i]为基础组成的，还有其他的nums[pos]，所以要+=
                    dp[i][j] += (dp[pos][i] + 1);
                }
                // 完成dp[i][j]更新之后，同步到rtn
                rtn += dp[i][j];
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    rtn = gua.numberOfArithmeticSlices(nums={2,4,6,8,10});
    cout << "expect value = 7, actual value = " << rtn << endl;

    rtn = gua.numberOfArithmeticSlices(nums={7,7,7,7,7});
    cout << "expect value = 16, actual value = " << rtn << endl;

    return 0;
}
