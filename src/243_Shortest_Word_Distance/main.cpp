
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int rtn = INT_MAX;// 也可以初始化为wordsDict.size()

        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word1)
                pos1 = i;
            if (wordsDict[i] == word2)
                pos2 = i;

            if (pos1 != -1 && pos2 != -1)
                rtn = min(rtn, abs(pos1- pos2));
        }

        return rtn;
    }
};

int main() {
  Solution gua;
  int rtn;
  vector<string> words;
  string w1, w2;

  rtn = gua.shortestDistance(words = {"practice", "makes", "perfect", "coding", "makes"}, w1 = "practice", w2 = "coding");
  cout << "expect value = 3, actual value = " << rtn << endl;

  rtn = gua.shortestDistance(words = {"practice", "makes", "perfect", "coding", "makes"}, w1 = "makes", w2 = "coding");
  cout << "expect value = 1, actual value = " << rtn << endl;

  return 0;
}

