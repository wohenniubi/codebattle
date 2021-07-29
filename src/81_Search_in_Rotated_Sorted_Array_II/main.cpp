
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 92.08%
    //Memory Usage: 14 MB, less than 29.12%
    bool search(vector<int>& nums, int target) {
        int lhs = 0, rhs = nums.size()-1;
        
        // 这样的话就可以取右边的值了
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            if (nums[mid] == target)
                return true;
            
            // 现在开始处理，当且仅当左右和mid都相等的时候，没有办法判断应该向哪边移动，所以直接压缩
            // 就像[1,1,1,3,1]和[1,3,1,1,1]，这种情况不可用于之前的处理
            if (nums[lhs] == nums[rhs] && nums[rhs] == nums[mid]) {
                ++lhs;
                --rhs;
            } else {
                // 这里面沿用之前的代码，就是用lhs,mid,rhs还有target来控制走向
                // 首先if决定形状，然后根据target和mid和边界决定方向
                if (nums[lhs] <= nums[mid]) {
                // if (nums[lhs] < nums[mid]) { //这里换成<就错了，太诡异了
                    if (target < nums[mid] && target >= nums[lhs]) {
                        rhs = mid-1;
                    } else {
                        lhs = mid+1;
                    }
                } else {
                    if (target > nums[mid] && target <= nums[rhs]) {
                        lhs = mid+1;
                    } else {
                        rhs = mid-1;
                    }
                }
                // if (nums[mid] > target) {
                //     // 仅有一种情况会让选择进入右半部分，因为只会旋转一次，所以一旦nums[lhs] >= nums[rhs]
                //     // 那么基本形状就确定了，再加一个target的比较，就妥妥确定左边右边了
                //     // if (nums[lhs] >= nums[rhs] && target < nums[rhs]) {
                //     // if (nums[mid] >= nums[rhs] && target < nums[rhs]) {
                //     if (nums[mid] >= nums[rhs] && target <= nums[rhs]) {
                //         lhs = mid +1;
                //     } else {
                //         rhs = mid -1;//大部分的情况是这样
                //     }
                // } else {
                //     // nums[mid] < target;
                //     // if (nums[lhs] >= nums[rhs] && target > nums[lhs]) {
                //     // if (nums[lhs] >= nums[mid] && target > nums[lhs]) {
                //     if (nums[lhs] >= nums[mid] && target >= nums[lhs]) {
                //         rhs = mid -1;
                //     } else {
                //         lhs = mid + 1;//大部分的情况是这样
                //     }
                // }
            }
            //cout << "lhs = " << lhs << ", mid = " << mid << ", rhs = " << rhs << endl;
        }
        
        return false;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    vector<int> nums;
    int target;
    
    rtn = gua.search(nums = {3,1}, target = 1);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.search(nums = {1,0,1,1,1}, target = 0);
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.search(nums = {1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1}, target = 13);
    cout << "expect value = 1, actual value = " << rtn << endl;

    return 0;
}
