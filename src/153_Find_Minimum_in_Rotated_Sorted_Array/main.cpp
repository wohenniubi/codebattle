#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // 思路必定是二分查找, 但是由于pivot的存在, 导致原本sorted的array变成了两部分
  // 而且还好这里没有duplicate的数字, 要不然更复杂一点
  //Runtime: 4 ms, faster than 93.14%
  //Memory Usage: 10.5 MB, less than 5.59%
  int findMin(vector<int>& nums) {
    int lhs = 0, rhs = nums.size()-1;
    while (lhs < rhs) {
      int mid = lhs + (rhs-lhs)/2;
      if (nums[mid] < nums[rhs]) {
        rhs = mid;
      } else {
        // 因为没有duplicate值，所以没有判断nums[mid] == nums[rhs]的情况;
        // followup问题里面要考虑
        lhs = mid+1;
      }
    }
    return nums[lhs];
    // 测试一下
    // [0] lhs=0, rhs=0; break, return nums[0]=0
    // [1,2] lhs=0, rhs=1; mid=0, nums[0]<nums[1], rhs=0; break, return nums[1]
    // [3,4,5,1,2], lhs=0, rhs=4; mid=2, nums[2]>nums[rhs], lhs=3; mid=3, nums[3]<nums[rhs], rhs=3; break, return nums[3]=1;
    // [4,5,6,7,0,1,2], lhs=0, rhs=6; mid=3, nums[3]>nums[6], lhs=4; mid=5, nums[5]<nums[6], rhs=5; mid=4, nums[4]<nums[5], rhs=4; break, return nums[4]=0
  }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> nums;
  rtn = gua.findMin(nums={3,4,5,1,2});
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.findMin(nums={4,5,6,7,0,1,2});
  cout << "expect value = 0, actual value = " << rtn << endl;

  return 0;
}

