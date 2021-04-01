
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 7.7 MB, less than 68.31%
    int rob(vector<int>& nums) {
        // 和股票问题一样的两状态问题，一个状态是是否抢nums[i]，另一个状态是i
        // 可以迭代+空间压缩，使得空间复杂度为O(1)
        int rob = nums[0], nrob = 0;
        for (int i = 1; i < nums.size(); ++i) {
            int tmp = rob;
            rob = nums[i] + nrob;// rob定义的是最后一家一定要抢的最大值
            nrob = max(tmp, nrob);// nrob定义的是最后一家不抢的最大值
        }
        return max(rob, nrob);
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> nums;
  rtn = gua.rob(nums={1,2,3,1});
  cout << "expect value = 4, actual value = " << rtn << endl;

  rtn = gua.rob(nums={2,7,9,3,1});
  cout << "expect value = 12, actual value = " << rtn << endl;

  return 0;
}


