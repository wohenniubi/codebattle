
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 97.45%
    //Memory Usage: 7.9 MB, less than 6.58%
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return 0;
        
        vector<int> incList{nums[0]};// 很巧妙的一个递增序列表，为每个num记录以它为结尾的最长子序列
        int maxLen = 1;
        for (int i = 1; i < len; ++i) {
            auto iter = lower_bound(incList.begin(), incList.end(), nums[i]);
            if (iter == incList.end()) {
                // 说明没有>= nums[i]的值，那么nums[i]就可以加到最后面，subsequence变长
                incList.push_back(nums[i]);
                maxLen = max(maxLen, (int)incList.size());
            } else {
                // 找到了大于等于nums[i]的数，那么这个数与incList最左端的距离就是能够组成subsequence的长度
                maxLen = max(maxLen, int(iter - incList.begin()) + 1);
                *iter = nums[i];
            }
        }
        
        return maxLen;
    }
    
    // 以下greedy方法不work，[1,3,6,7,9,4,10,5,6]，输出应该是6
    int lengthOfLIS1(vector<int>& nums) {
        // DP算法
        int len = nums.size();
        if (len == 0) return 0;//又想坑我是不是
        vector<int> st{nums[0]};
        int rtn = 1;
        for (int i = 1; i < len; ++i) {
            // 题目不够明确，[2,2]要求输出1，所以咯，要包括==
            // while (st.size() && nums[i] < st.back()) {
            while (st.size() && nums[i] <= st.back()) {
                // 只有装入最小的num，才有可能产生最长的subsequence
                st.pop_back();
            }
            st.push_back(nums[i]);
            rtn = max(rtn, (int)st.size());
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;

    rtn = gua.lengthOfLIS(nums={2, 2});
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.lengthOfLIS(nums={1,3,6,7,9,4,10,5,6});
    cout << "expect value = 6, actual value = " << rtn << endl;

    rtn = gua.lengthOfLIS(nums={10,9,2,5,3,7,101,18});
    cout << "expect value = 4, actual value = " << rtn << endl;
    
    return 0;
}
