
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 24 ms, faster than 98.24%
    //Memory Usage: 36.2 MB, less than 23.00%
    int findMaxConsecutiveOnes(vector<int>& nums) {
        // 和先前那道最长替换字符的题类似，貌似还要简单一些
        int lhs = 0, rtn = 0;//rhs = 0 也太大意了吧，滑动窗右边界是i呀
        int cnt = 0;// 存储的是零的index
        
        for (int i = 0; i < nums.size(); ++i) {
            if (0 == nums[i])
                ++cnt;
            
            // 现在计算[lhs, rhs]这个区间的长度，以及其中0的个数
            while (cnt > 1) {
                if (nums[lhs] == 0)
                    --cnt;
                ++lhs;
            }
            // 跳出while循环时必定cnt<=0，此时的窗长就是rtn
            //rtn = max(rhs - lhs + 1, rtn);//太大意了，滑动窗右边界是i呀
            rtn = max(i - lhs + 1, rtn);
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    
    rtn = gua.findMaxConsecutiveOnes(nums={1,0,1,1,0});
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.findMaxConsecutiveOnes(nums={1,0,1,1,0,1});
    cout << "expect value = 4, actual value = " << rtn << endl;
    return 0;
}
