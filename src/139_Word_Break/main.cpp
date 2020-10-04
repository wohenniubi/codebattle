
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
  //Runtime: 8 ms, faster than 84.58% 
  //Memory Usage: 9.2 MB, less than 77.34%
  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_map<string, bool> dict;
    //for (auto & word : wordDict) dict.insert(word);

    return checkWordValid(s, 0, wordDict, dict);
  }

  bool checkWordValid(string &s, int pos,
    vector<string>& wordDict, unordered_map<string, bool> &dict) {
    if (pos >= s.size()) return true;

    string tmp = s.substr(pos);
    auto iter = dict.find(tmp);
    if (iter != dict.end()) {
      return iter->second;
    }

    bool rtn = false;
    for (auto & word : wordDict) {
      if (word.size() > (s.size() - pos) || word != s.substr(pos, word.size())) continue;//大意啦没有写这句
      
      rtn |= checkWordValid(s, pos+word.size(), wordDict, dict);
      if (rtn) break;
    }
    return dict[tmp] = rtn;
  }
};

int main() {
  Solution gua;
  bool rtn;
  string s;
  vector<string> wordDict;

  rtn = gua.wordBreak(s="leetcode", wordDict={"leet", "code"});
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.wordBreak(s="applepenapple", wordDict={"apple", "pen"});
  cout << "expect value = 1, actual value = " << rtn << endl;

  rtn = gua.wordBreak(s="catsandog", wordDict={"cats", "dog", "sand"});
  cout << "expect value = 0, actual value = " << rtn << endl;

  return 0;
}

