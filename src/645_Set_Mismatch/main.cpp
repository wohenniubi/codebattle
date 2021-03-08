
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 24 ms, faster than 95.75%
    //Memory Usage: 21.3 MB, less than 89.93%
    vector<int> findErrorNums(vector<int>& nums) {
        // 我能想到的是之前一道题的变形
        // 遍历一遍可以找到缺失的数，再遍历一遍可以得到与这个缺失的数的差值，然后就可以得到重复的数
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            // 这个while可以确保nums[i] == nums[nums[i]-1]，物理意义就是nums[i]这个值存储于nums[i]-1这个index，这就是我们希望的情况
            while (nums[i] != nums[nums[i]-1]) {
                // 会不会出现死循环？？
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        
        int diff = 0, pos = 0;
        for (int i = 0; i < size; ++i) {
            if (nums[i] != (i+1)) {
                pos = i+1;
            }
            diff += (nums[i] - (i+1));
        }
        // 这个循环之后，pos指向缺失的数字，diff表明与[1,n]这个数列的差，如果为负，说明缺失的数被替换为了较小的数，反之为替换为了较大的数
        // diff等于0说明没有缺失任何数字，pos+diff是重复的数字，pos是缺失的数字
        // return (diff>0)? {pos, pos+diff}: {pos+diff, pos};
        return {pos+diff, pos};
    }
};

ostream &operator<<(ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn) os << val << ", ";
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> nums, rtn;
    
    rtn = gua.findErrorNums(nums = {1,2,2,4});
    cout << "expect result = [2,3], actual result = " << rtn << endl;

    rtn = gua.findErrorNums(nums = {1,1});
    cout << "expect result = [1,2], actual result = " << rtn << endl;
    return 0;
}
