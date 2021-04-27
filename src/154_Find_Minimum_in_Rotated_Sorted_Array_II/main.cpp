
#include <iostream>
#include <vector>

using namespace std;
 
class Solution {
public:
    //Runtime: 4 ms, faster than 91.06%
    //Memory Usage: 12.2 MB, less than 48.73%
    int findMin(vector<int>& nums) {
        int size = nums.size();
        
        // 假如是[2,2,2,1]，或者[1,2,2,2]，或者[2,2,1,2]，或者[2,1,2,2]
        // 或者是[2,2,1]，或者[2,1,2]，[1,2,2]
        
        int lhs = 0, rhs = size-1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs-lhs)/2;
            if (nums[mid] < nums[rhs]) {
                rhs = mid;// 发现了一个可能的前进方向
            } else if (nums[mid] == nums[rhs]) {
                rhs--;
            } else {
                // nums[mid] > nums[rhs];
                lhs = mid+1;
            }
        }
        
        return nums[lhs];
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<int> nums;
    rtn = gua.findMin(nums = {1,3,5});
    std::cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.findMin(nums = {2,2,2,0,1});
    std::cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}
