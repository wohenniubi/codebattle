
#include <iostream>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        // 不就是遍历吗？？
        // int len1 = s.size(), len2 = t.size();

        int i = 0, j = 0;
        bool isSub = false;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
                j++; // 都向右移动一位
            } else {
                j++;
            }
        }

        // 如果没找到，那么i必定还没有移动到s的结尾
        return i == s.size();
    }
};

int main() {
  Solution gua;
  string s, t;
  bool rtn;

  rtn = gua.isSubsequence(s="abc", t="ahbgdc");
  cout << "expect value = 1, actual value = " << rtn << endl;
  
  rtn = gua.isSubsequence(s="axc", t="ahbgdc");
  cout << "expect value = 0, actual value = " << rtn << endl;
  
  return 0;
}

