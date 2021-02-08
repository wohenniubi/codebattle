
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 这个函数是统一的nSum函数，是由3Sum，4Sum总结而来
    // 不过如果自顶向下的看的话，就是递归，逐步将nSum减少为n-1Sum，直到2Sum； 注意要去掉重复
    // void nSum(vector<int>& nums, vector<vector<int>> &rtn, int target, int n, int bgn, int end) {
    vector<vector<int>> nSum(vector<int>& nums, int target, int n, int bgn, int end) {
        vector<vector<int>> rtn;
            
        if (n == 2) {
            if (bgn + 1 >= end) return {};
            
            // 现在是bgn < end -1，这样至少有两个element了
            int lhs = bgn, rhs = end-1;
            while (lhs < rhs) {
                //int sum = nums[bgn] + nums[rhs]; 大意了哇，写错了哇
                int sum = nums[lhs] + nums[rhs];
                if (sum == target) {
                    //rtn.push_back({nums[bgn], nums[rhs]}); 一定要小心呀，不要浮躁
                    rtn.push_back({nums[lhs], nums[rhs]});
                    // 这之后要同时缩小lhs和rhs
                    ++lhs; --rhs;
                    
                    // 为了避免重复，还要继续操作lhs和rhs
                    //while (lhs < rhs && nums[rhs] == nums[rhs-1]) --rhs;
                    //while (lhs < rhs && nums[lhs] == nums[lhs+1]) ++lhs;
                    while (lhs < rhs && nums[rhs] == nums[rhs+1]) --rhs;// 此时rhs+1已经算过
                    while (lhs < rhs && nums[lhs] == nums[lhs-1]) ++lhs;// 此时lhs-1已经算过
                } else if (sum > target) {
                    rhs--;// 缩小rhs
                } else {
                    lhs++;// 增大lhs
                }
            }
        } else {
            // 计算n-1 Sum
            // for (int i = bgn; i < end; ++i) {
            for (int i = end-1; i >= bgn; --i) {
                int newT = target - nums[i];
                // 去掉nums[i]之后，就是对剩下的[i+1, end) 区间进行就n-1Sum，其中以target-nums[i]作为目标
                // vector<vector<int>> rtn = nSum(nums, rtn, newT, n-1, i+1, end);
                vector<vector<int>> subs = nSum(nums, newT, n-1, bgn, i);
                for (auto & sub : subs) {
                    sub.push_back(nums[i]);
                    rtn.push_back(sub);
                }
                
                // 这里注意要去掉可能的重复，如果nums[i] == nums[i+1]
                // 那么要跳过nums[i+1]作为第一个element的情况，[-1,-1,0,1,2]
                // 而一旦使用索引，就要注意合法性
                // while (i+1 < end && nums[i] == nums[i+1]) ++i;
                while (i-1 >= bgn && nums[i] == nums[i-1]) --i;
                // 跳出while循环说明到头了，或者nums[i+1] != nums[i]
            }
        }
        return rtn;
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};
        
        // nSum有两种基本思路：sort然后快慢索引，然后是哈希表查找
        sort(nums.begin(), nums.end());
        //return nSum(nums, 3, 0, 0, nums.size()); 第二个值是target
        return nSum(nums, 0, 3, 0, nums.size());
    }
};

ostream &operator<<(ostream& os, vector<vector<int>> &rtn) {
    os << "[";
    for (auto & sub : rtn) {
        os << "[";
        for (auto val : sub) {
            os << val << ", ";
        }
        os << "], ";
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<vector<int>> rtn;
    
    vector<int> nums;
    rtn = gua.threeSum(nums = {-1,0,1,2,-1,-4});
    cout << rtn << endl;
    
    return 0;
}

