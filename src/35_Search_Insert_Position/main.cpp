
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 9.4 MB, less than 99.51%
    int searchInsert(vector<int>& nums, int target) {
        // 因为要找到最适合插入target的index，所以我觉得两种写法里面<要好一些，因此对应的rhs就是size()
        int lhs = 0, rhs = nums.size();
        
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                rhs = mid;// 选择左半区间时更新右边界，没毛病
            } else {
                lhs = mid + 1;
            }
        }
        return lhs;// 跳出while循环时lhs==rhs，然后是大于target的地方，说得通
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<int> nums;
    int target, rtn;
    
    rtn = gua.searchInsert(nums = {1,3,5,6}, target = 5);
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.searchInsert(nums = {1,3,5,6}, target = 2);
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
