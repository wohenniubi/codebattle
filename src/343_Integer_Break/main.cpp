
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.4 MB, less than 10.73%
    int integerBreak(int n) {
        // 虽然第一时间想到要用分支方法+DFS+memorize，但是再一想，貌似还是递归要好一丢丢
        vector<int> maxP(n+1,1);// n的范围是[2,58]，所以时间复杂度O(n*n)还是勉强凑合
        for (int i = 2; i <= n; ++i) {
            // 内部循环虽然要遍历所有小于i的情况，但是由于乘法是对称的，所以算一半就可以了
            for (int j = 1; j <= i/2; ++j) {
                maxP[i] = max(maxP[i], maxP[j]*max(maxP[i-j], i-j));
                maxP[i] = max(maxP[i], j * (i-j));
                maxP[i] = max(maxP[i], j * maxP[i-j]);// 确实大意了，应该再多举一个例子的，n=8时，输出为18
            }
        }
        // Example1: n = 2;  i = [2,2];  j = [1,1], maxP[1] = 1, 所以maxP[2]为1
        // Example2: n = 10; i = [2,10];
        //           当i = 3, j = [1,1], 此时maxP[1]*maxP[i-1=2] = 1, maxP[1]*(i-1) = 2, 所以maxP[3] = 2
        //           当i = 4, j = [1,2], 当j=1, maxP[1]*maxP[i-1=3] = 2, maxP[1]*(i-1) = 3, 1 *(i-1) = 3
        //                               当j=2, maxP[2]*maxP[i-2=2] = 1, maxP[2]*(i-2) = 2, 2 *(i-2) = 4, 所以maxP[4] = 4
        //           当i = 5，j = [1,2]  当j=1, maxP[1]*maxP[i-1=4] = 4, maxP[1]*(i-1) = 4, 1 *(i-1) = 4
        //                               当j=2, maxP[2]*maxP[i-2=3] = 2, maxP[2]*(i-2) = 3, 2 *(i-2) = 6, 所以maxP[5] = 6
        return maxP.back();
    }
};

int main() {
  Solution gua;
  int rtn, n;

  rtn = gua.integerBreak(n = 2);
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.integerBreak(n = 8);
  cout << "expect value = 18, actual value = " << rtn << endl;

  rtn = gua.integerBreak(n = 10);
  cout << "expect value = 36, actual value = " << rtn << endl;

  return 0;
}

