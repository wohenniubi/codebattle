#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 12 ms, faster than 96.10%
    //Memory Usage: 11.6 MB, less than 100.00%
    int singleNonDuplicate(vector<int>& nums) {
        //因为是sorted而且要求时间复杂度为O(logn)，那么只有用二分查找了
        //关键是当下的比较函数是啥，把nums[mid]与左边和右边进行比较哇
        //因为只有一个数是单的，其他的数可能等于左边或者右边
        nums.insert(nums.begin(), -1);
        nums.push_back(-1);// 因为提示说0 <= nums[i] <= 10^5
        
        // [1,1,2] -> [-1,1,1,2,-1] lhs = 1, rhs = 3, 这样就不用担心越界了
        int lhs = 1, rhs = nums.size()-2;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            // lhs,lhs+1...lhs + (rhs - lhs)/2,lhs + (rhs - lhs)/2+1,...rhs
            // 总长度是rhs-lhs+1
            // len([lhs,mid-1]) = (rhs-lhs)/2
            // len([lhs,mid]) = (rhs-lhs)/2 + 1;
            // len([mid+1,rhs]) = (rhs-lhs)/2;
            
            // 去掉中间一对之后，判断左右部分的奇偶性，来修改lhs或者rhs，朝着奇数那边走
            int tmp = (rhs-lhs)/2;
            if (nums[mid-1]==nums[mid]) {
                // [1,1,2] lhs = 1, rhs = 3; mid = 2, nums[1]==nums[2]
                // 去掉中间一对之后变成左边(rhs-lhs)/2-1， 右边(rhs-lhs)/2，如果tmp是奇数，则lhs=mid+1
                if (tmp % 2) lhs= mid+1;
                else rhs= mid;//mid-1; 不能过多的去掉，否则会导致miss
                // [1,4,4,8,8], lhs = 1, rhs = 5; mid = 3, nums[2]==nums[3], 向左移动, rhs=3
            } else if (nums[mid+1]==nums[mid]) {
                // [1,2,2] lhs = 1, rhs = 3; mid = 2, nums[2]==nums[3]
                // [1,1,2,3,3,4,4] lhs =1, rhs = 7; mid=4, nums[4]==nums[5]
                // [1,2,2,3,3,4,4] lhs =1, rhs = 7; mid=4, nums[4]==nums[5]
                // [1,2,2,3,3,4,4] lhs =1, rhs = 7; mid=4, nums[4]==nums[5]
                // 去掉中间一对之后变成左边(rhs-lhs)/2，右边(rhs-lhs)/2-1，如果tmp是奇数，则rhs=mid
                if (tmp % 2) rhs= mid-1;
                else lhs = mid;//mid+1; 不能过多的去掉，否则会导致miss
            } else {
                // mid与左右两边都不等，就是所求
                // [1,1,2,3,3] lhs = 1, rhs = 5; mid = 3, nums[2]
                return nums[mid];
            }
        }
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    rtn = gua.singleNonDuplicate(nums={1,1,2,2,3});
    cout << "expect value = 3, actual value = " << rtn << endl;
    return 0;
}

