
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 74.67%
    //Memory Usage: 10.6 MB, less than 18.50%
    int minSubArrayLen(int target, vector<int>& nums) {
        // 由于是positive的，所以可以考虑滑动窗
        int lhs = 0;
        //int sum = 0, rtn = nums.size();//大意了，如果刚好rtn结果等于nums.size()，这个值就无法区分是否发生修改
        int sum = 0, rtn = nums.size()+1;
        
        for (int rhs = 0; rhs < nums.size(); ++rhs) {
            sum += nums[rhs];
            // 滑动窗，先加右边，判断条件，再动左边
            //while (sum >= target) // 如果target为负，可能就有问题，所以下面的写法要好一点
            while (lhs <= rhs && sum >= target) {
                rtn = min(rtn, rhs - lhs + 1);
                sum -= nums[lhs];
                ++lhs;
            } // 修改if为while，因为要不断的修改lhs
            
            // 从左到右处理，处理完左边之后，就不会再修改了，能够满足这个条件是因为nums[pos]，否则还可以继续右滑
        }
        
        //return (rtn == nums.size())? 0: rtn;
        return (rtn == nums.size()+1)? 0: rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, target;
    vector<int> nums;
    
    rtn = gua.minSubArrayLen(target = 11, nums={1,1,1,1,1});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.minSubArrayLen(target = 4, nums={1,4,5});
    cout << "expect value = 1, actual value = " << rtn << endl;
    
    rtn = gua.minSubArrayLen(target = 15, nums={1,2,3,4,5});
    cout << "expect value = 5, actual value = " << rtn << endl;
    return 0;
}
