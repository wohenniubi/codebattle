
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 用DP搞不定的原因在于没有进行全局考虑，导致结果是一个sub optimal
    // 而全局考虑的话，DP的模版搞不定这k个集合，于是只好用back tracking的方式，
    // 要把所有的数、k作为参数，一气呵成，有点像cherry pickup那题，前后路径要一起考虑
    //Runtime: 16 ms, faster than 52.96%
    //Memory Usage: 9.4 MB, less than 44.70%
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (auto & num : nums) sum+= num;
        if (sum%k) return false;//先判断整体能否拆分为k个组
        sum/= k;
        for (auto & num : nums)
            if (num > sum) return false;//如果存在大于sum/k的数字将无法分组（因为都是正数）

        vector<int> visited(nums.size());// 题目说nums.len() < 16，那就不用哈希表了
        return helper(nums, sum, k, 0, sum, visited);
    }
    
    // 这个函数会告知是否可以拆分为k个subset：
    // target是每个subset的目标，curSum是subset当前的值；
    // 过滤用过的数采用visit数组
    bool helper(vector<int> &nums, int target, int k, int pos, int curSum, vector<int> &visited) {
        // 返回条件要看k、target和curSum， 不确定的话先放一放
        if (curSum == 0) {
            if (k == 1) {
                return true;
                //没有subset凑成了target且不再需要多余的分组，若要再保险的话，检查一下visited? 应该不需要了因为都是正整数
            } else {
                //return helper(nums, target, k-1, pos, 0, visited);
                //别大意，pos从0开始，避免漏掉选项，visited过滤重复
                return helper(nums, target, k-1, 0, target, visited);
            }
        }
        if (curSum < 0) return false;// 加了这么一行代码，瞬间QoR改进
        //    Runtime: 4 ms, faster than 95.06%
        //    Memory Usage: 9.2 MB, less than 80.12%


        for (int i = pos; i < nums.size(); ++i) {
            if (visited[i]) continue;
            visited[i] = true;
//            if (!helper(nums, target, k, i+1, curSum+nums[i], visited))
//                return false; 不对，应该是没有找到则继续找
            if (helper(nums, target, k, i+1, curSum-nums[i], visited))
                return true;// 找到一个则立即返回
            visited[i] = false;
        }
        return false;// 为啥返回false呢？因为for loop中如果出现一个合法的解就立即返回，因此剩下的都是不合法的
    }


    // 方法1不work，出现suboptimal的解 
    bool canPartitionKSubsets1(vector<int>& nums, int k) {
        int sum = 0;
        for (auto & num : nums) sum+= num;
        if (sum%k) return false;//先判断整体能否拆分为k个组
        sum/= k;
        for (auto & num : nums)
            if (num > sum) return false;//如果存在大于sum/k的数字将无法分组（因为都是正数）
        
        while (k--) {
            vector<int> sel = helper(nums, sum);
            if (sel.empty()) return false;
            
            // 更新一下nums；从后往前删除
            for (int i = sel.size()-1; i >= 0; --i) {
                nums.erase(nums.begin()+sel[i]);
            }
        }
        return true;
    }
    
    // 返回的是选择的integer在nums里面的index，这个函数就是背包问题了，需要新增一个list存index
    vector<int> helper(vector<int> &nums, int k) {
        unordered_map<int, vector<int>> dict;
        vector<int> dp(k+1);
        for (int j = 0; j < nums.size(); ++j) {
            int num = nums[j];
            for (int i = k; i > 0; --i) {
                if (i >= num) {
                    // dp[i] = max(dp[i-num]+num, dp[i]);
                    if (dp[i-num]+num > dp[i]) {
                        dp[i] = dp[i-num]+num;
                        // dict[i] = dp[i-num]; 大意了
                        dict[i] = dict[dp[i-num]];
                        dict[i].push_back(j);
                    }
                    // else {
                    //     dp[i] = dp[i];
                    //     dict[i] = dict[i];
                    // }
                }
            }
        }
        //return dict[dp[k]];// 返回的是dp[k]的vector
        return (dp[k] == k)? dict[dp[k]]: vector<int>();
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    int k;
    vector<int> nums;
    // 跪在这个case了，greedy的选了[10,10,10]，导致剩下的不能凑出sum=30
    rtn = gua.canPartitionKSubsets(nums = {10,10,10,7,7,7,7,7,7,6,6,6}, k=3);
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.canPartitionKSubsets(nums = {2,2,2,2,3,4,5}, k=4);
    cout << "expect value = 0, actual value = " << rtn << endl;
    
    rtn = gua.canPartitionKSubsets(nums = {4, 3, 2, 3, 5, 2, 1}, k=4);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
