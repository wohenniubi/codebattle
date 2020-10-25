#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 8.1 MB, less than 100.00%
    int rob(vector<int>& nums) {
        int size = nums.size();
        if (!size) return 0;
        
        int rob1[2], nrob1[2];
        rob1[0] = rob1[1] = nums[0];
        nrob1[0] = nrob1[1] = 0;//大意了，如果用array的形式，一定要初始化，要不然nrob1里面是垃圾数据
        
        // 完全背包问题的变种，rob1表示抢第一家，nrob1表示不抢第一家
        for (int i = 2; i < size-1; ++i) {
            // rob[i] = max(rob[i-1], rob[i-2]+nums[i])
            swap(rob1[0], rob1[1]);
            rob1[1] = max(rob1[1] + nums[i], rob1[0]);
        }
        for (int i = 1; i < size; ++i) {
            // 相同的操作给nrob1
            swap(nrob1[0], nrob1[1]);
            nrob1[1] = max(nrob1[1] + nums[i], nrob1[0]);
        }

        // 最后判断一次[size-1]这一家
        return max(rob1[1],nrob1[1]);
    }

    int rob1(vector<int>& nums) {
        int n = nums.size();
        if (n < 1) return 0;
        // 极限情况, 只有1个值; 后面的helper函数无法处理
        int rtn = nums[0];
        // 一次DP解决不了, 那就两次
        rtn = max(rtn, helper(nums, 0, n-2));//去掉最后一个房间, 用house robber I的方法
        rtn = max(rtn, helper(nums, 1, n-1));//去掉第一个房间, 用house robber I的方法
        return rtn;
    }
    
    int helper(vector<int>& nums, int bgn, int end) {
        int n = end-bgn+1;
        if (n < 1) return 0;
        vector<int> dp(n+1,0);
        dp[1] = nums[bgn];//nums[0], 得修改为当前得bgn
        for (int i = bgn+1; i <= end; ++i) {
            // for循环的i范围是正确的
            // 但是i需要转换为dp的index, 必须减去bgn
            // dp[i+1] = max(dp[i], dp[i-1] + nums[i]);
            dp[i+1-bgn] = max(dp[i-bgn], dp[i-1-bgn] + nums[i]);
        }
        return dp.back();
    }
};

int main() {
    Solution gua;
    int rtn;
    vector<int> nums2{1,2,1,1};
    rtn = gua.rob(nums2);
    cout << "expect value = 3, actual value = " << rtn << endl;    

    vector<int> nums1{1,2,3,1};
    rtn = gua.rob(nums1);
    cout << "expect value = 4, actual value = " << rtn << endl;    

    return 0;
}
