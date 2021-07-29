
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 8 ms, faster than 22.84%
    //Memory Usage: 11.1 MB, less than 28.17%
    // 采用二分法啦，然后由于会使用左右边界的值来辅助查找，所以采用第一种写法lhs <= rhs
    int search(vector<int>& nums, int target) {
        int lhs = 0, rhs = nums.size()-1;
        
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (nums[mid] == target)
                return mid;
            
            // 然后是模版的处理，只不过每个分支里面还要判断旋转的情况
            if (nums[mid] > target) {
                // 在mid > target时，正常情况是查找左分支，但在本题的情况下，仅有一种情况需要反常识查找右分支
                //if (nums[mid] > nums[rhs] && target < nums[rhs]) { 大意了，target可能就是nums[rhs]
                if (nums[mid] > nums[rhs] && target <= nums[rhs]) {
                    lhs = mid + 1;//nums[mid] > nums[rhs] 限制了旋转的形状，然后target和右边相比，确定了所在分段
                } else {
                    rhs = mid - 1;
                }
            } else {
                // 在mid < target时，正常情况是查找右分支，但本题的情况下，仅有一种情况需要反常识查找左分支
                //if (nums[mid] < nums[rhs] && target > nums[rhs]) {
                if (nums[mid] < nums[lhs] && target >= nums[lhs]) {
                    rhs = mid - 1;
                } else {
                    lhs = mid + 1;
                }
            }
        }
        
        return -1;// 如果没有找到就返回，此时lsh = rhs +1
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn, target;
    vector<int> nums;

    rtn = gua.search(nums = {3, 1}, target = 1);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.search(nums = {4,5,6,7,0,1,2}, target = 0);
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.search(nums = {4,5,6,7,0,1,2}, target = 3);
    cout << "expect value = -1, actual value = " << rtn << endl;

    rtn = gua.search(nums = {1}, target = 0);
    cout << "expect value = -1, actual value = " << rtn << endl;

    return 0;
}
