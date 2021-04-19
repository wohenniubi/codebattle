
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // 使用的是bitwise操作
        int rtn = 0;
        int size = nums.size();
        for (int i = 0; i < 32; ++i) {
            int sum = 0;

            for (int j = 0; j < size; ++j) {
                // 取每个num的第i位，进行异或
                // sum += ((1<<i) & nums[j]);
                sum += ((nums[j] >> i) &1);// 统计第i位的bit的个数
            }

            sum %= 3;
            if (sum)
                rtn ^= (1<<i);// 把第i位的bit设置到rtn
        }

        return rtn;
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<int> nums;

  rtn = gua.singleNumber(nums={2,2,3,2});
  cout << "expect value = 3, actual value = " << rtn << endl;
  
  rtn = gua.singleNumber(nums={0,1,0,1,0,1,99});
  cout << "expect value = 99, actual value = " << rtn << endl;
  
  return 0;
}

