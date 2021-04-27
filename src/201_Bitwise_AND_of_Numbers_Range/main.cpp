
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 4 ms, faster than 89.64%
    //Memory Usage: 5.7 MB, less than 93.80%
    int rangeBitwiseAnd(int left, int right) {
        // 就是计算区间[left, right]中所有数字的共同MSB部分，也就是算left和right的共同MSB部分
        int m = left, n = right;
        int cnt = 0;// 记录右移移位次数
        while (m != n) {
            m = m >> 1;
            n = n >> 1;
            ++cnt;
        }
        // 跳出while循环时的m和n相等了，是公共的头部
        return m << cnt;
    }
};

int main() {
  Solution gua;
  int rtn, left, right;
  rtn = gua.rangeBitwiseAnd(left = 1, right = 2147483647);
  cout << "expect value = 0, actual value = " << rtn << endl;

  rtn = gua.rangeBitwiseAnd(left = 5, right = 7);
  cout << "expect value = 4, actual value = " << rtn << endl;
  return 0;
}

