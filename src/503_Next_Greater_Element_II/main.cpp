
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 32 ms, faster than 96.13%
    //Memory Usage: 23.6 MB, less than 98.91%
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.empty()) return {};
        
        // 我想的办法是再绕一圈呗，然后index取mod
        int len = nums.size();
        vector<int> rtn(len, -1);
        vector<int> s;
        for (int i = 0; i < 2*len; ++i) {
            int pos = i%len; // 将i映射到合法区间
            // 因为是pop时才修改index，而从左到右遍历为了不在相等时触发pop，需要跳过=
            while (s.size() && nums[pos] > nums[s.back()]) {
                // 避免重复修改rtn
                if (rtn[s.back()] == -1) {
                    rtn[s.back()] = pos;//修改上一个数的greater number index为当前pos
                }
                // 去掉s中的较小值
                s.pop_back();
            }
            // 再加入s里面
            s.push_back(pos);
        }
        
        // 再来一次把index换成值
        //for (int i = 0; i < len; ++i) rtn[i] = nums[rtn[i]]; 大意了，index有-1哟
        for (int i = 0; i < len; ++i) rtn[i] = (rtn[i]!=-1)?nums[rtn[i]]: -1;
        return rtn;
    }
};

ostream & operator<<(ostream & os, vector<int> & rtn) {
    os << "[";
    for (auto val : rtn) os << val << ",";
    os << "]" << endl;
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> rtn, nums, exp;
    rtn = gua.nextGreaterElements(nums = {1,2,1});
    exp = {2,-1,2};
    cout << "expect result = " << exp << endl;
    cout << "actual result = " << rtn << endl;
    return 0;
}

