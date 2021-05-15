#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 32 ms, faster than 77.48%
    //Memory Usage: 18.4 MB, less than 54.97%
    // 这种方法是在每一层里面进行两种选择, 这样总共n层, 就有2^n个组合, 但是要想清楚两种选择如何区分;
    // 本题中区分的方式是将当前位置的char变成数字, 或者保持为char;
    void helper(string &word, int pos, int cnt, string path, vector<string> &rtn) {
        if (pos == word.size()) {
            // 不要大意啊, cnt为0不需要转换为string
            // path += to_string(cnt);// 返回条件, 当达到最末端之后把当前所有的数字变成string, 叠加到path后面再返回
            path += cnt? to_string(cnt):"";
            // 不要大意啊, 怎么忘记把path加到rtn这个背包里面
            rtn.push_back(path);
            return;// path; 不要大意嘛, 不需要返回值
        }
        helper(word, pos+1, cnt+1, path, rtn);// 这个分支对应数字替换的情况
        // 这里也不要大意啊, cnt为0不需要转换为string
        // helper(word, pos+1, 0, path+to_string(cnt)+word[pos], rtn);// 这个分支对应保持当前char的情况
        helper(word, pos+1, 0, path+(cnt?to_string(cnt):"")+ word[pos], rtn);
    }

    vector<string> generateAbbreviations(string word) {
        vector<string> rtn;
        helper(word, 0, 0, "", rtn);
        //backtrack(word, "", 0,0,0,0, rtn);
        return rtn;
    }
};

ostream &operator<<(ostream &os, vector<string> &rtn) {
  os << "[";
  for (auto & word : rtn) 
    os << word << ", ";

  os << "]";
  return os;
}

int main() {
  Solution gua;
  string word;
  vector<string> rtn;
  rtn = gua.generateAbbreviations(word="word");
  cout << "The abbreviation of " << word << " is\n" << rtn << endl;
  return 0;
}

