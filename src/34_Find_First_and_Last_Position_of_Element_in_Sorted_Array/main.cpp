#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    //Runtime: 16 ms, faster than 86.01%
    //Memory Usage: 13.8 MB, less than 100.00%
    vector<int> searchRange(vector<int>& nums, int target) {
      //if (nums.empty()) return {};//大意了，应该是{-1,-1}, 不是空
      if (nums.empty()) return {-1, -1};

      // 感觉就是实现multiple map或者set的equal_range;
      auto iterLb = lower_bound(nums.begin(), nums.end(), target);
      auto iterUb = upper_bound(nums.begin(), nums.end(), target);
      if (iterLb == end(nums) || *iterLb != target) {
        // 说明所有的值都小于target或者找不到target
        return {-1,-1};
      }
      return {int(iterLb-nums.begin()), int(iterUb-nums.begin()-1)};
    }
};

ostream & operator<<(ostream &os, vector<int> &rtn) {
  os << "[";
  for (auto pos : rtn) os << pos << ", ";
  os << "]";
  return os;
}

int main() {
  Solution gua;
  vector<int> rtn, nums;
  int target;

  rtn = gua.searchRange(nums={5,7,7,8,8,10}, target=8);
  cout << "expect value = [3,4], actual value = " << rtn << endl;

  rtn = gua.searchRange(nums={5,7,7,8,8,10}, target=6);
  cout << "expect value = [-1,-1], actual value = " << rtn << endl;

  rtn = gua.searchRange(nums={}, target=0);
  cout << "expect value = [-1,-1], actual value = " << rtn << endl;

  return 0;
}

