
#include <iostream>

using namespace std;

class Solution {
public:
    // 检查"3d"是不是"word"的缩写词
    bool validWordAbbreviation(string pattern, string abbr) {
        // 字符串比较了，双索引
        int lhs = 0, rhs = 0, num = 0;
        while (lhs < abbr.size() && rhs < pattern.size()) {
            if (isdigit(abbr[lhs])) {
                num = num*10 + (abbr[lhs] - '0');
                ++lhs;
                if (lhs == abbr.size())
                    rhs += num;
            } else {
                rhs += num;
                if (abbr[lhs] != pattern[rhs])
                    return false;
                ++lhs; ++rhs;
            }
        }
        // 跳出循环时可能是其中一方不满足条件
        return lhs == abbr.size() && rhs == pattern.size();
    }
};

int main() {
  Solution gua;
  string abbr, pattern;
  bool rtn;

  rtn = gua.validWordAbbreviation(pattern = "internationalization", abbr = "i12iz4n");
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.validWordAbbreviation(pattern = "word", abbr = "4");
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.validWordAbbreviation(pattern = "word", abbr = "2");
  cout << "expect value = 0, actual value = " << rtn << endl;

  return 0;
}

