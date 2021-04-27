
#include <iostream>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 5.8 MB, less than 77.57%
    int hammingWeight(uint32_t n) {
        uint32_t tmp = n;
        int rtn = 0;
        while (tmp) {
            tmp -= (tmp & -tmp);// tmp &= -tmp;
            ++rtn;
        }
        return rtn;
    }
};

int main() {
  Solution gua;
  int rtn;
  uint32_t n;
  rtn = gua.hammingWeight(n = 11);
  cout << "expect value = 3, actual value = " << rtn << endl;
  
  rtn = gua.hammingWeight(n = 128);
  cout << "expect value = 1, actual value = " << rtn << endl;
  
  rtn = gua.hammingWeight(n = -3);
  cout << "expect value = 31, actual value = " << rtn << endl;
  
  return 0;
}

