
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 漂亮的双pointer做法，干脆不保存对S的统计，直接干
    // Runtime: 4 ms, faster than 98.33%
    // Memory Usage: 8 MB, less than 80.57%
    int expressiveWords(string S, vector<string>& words) {
        int lenS = S.size(), cnt = 0;
        
        function<bool(string &word)> isStrethy = [&](string & word) {
            int indxS = 0, indxW = 0;
            while (indxS < S.size() && indxW < word.size()) {
                int preS = indxS, preW = indxW;
                while (indxS < S.size() && S[preS] == S[indxS]) {
                    indxS++;
                }
                while (indxW < word.size() && word[preW] == word[indxW]) {
                    indxW++;
                }
                // 此时要比较[preS,indxS)和[preW,indxW)这部分是否可以strethy
                if ((S[preS] == word[preW])
                    && ((indxS-preS) == (indxW-preW)
                        || ((indxS-preS) > (indxW-preW) && (indxS-preS) >= 3))) {
                    preS = indxS;
                    preW = indxW;
                } else {
                    return false;
                }
            }
            // return true;// 这个判断太松了，对于S="abcd",word="abc"的情况会错误
            return (indxS == S.size() && indxW == word.size());
        };
        for (auto & word : words) {
            if (isStrethy(word))
                cnt++;
        }
        
        return cnt;
    }

    //Runtime: 12 ms, faster than 39.15%
    //Memory Usage: 9 MB, less than 35.94%
    int expressiveWords1(string S, vector<string>& words) {
        // 貌似很简单？？有点像run-length coding， 不过问题的难点是如何来表示这个run-length coding的pattern
        int rtn = 0;
        
        // 特殊处理
        if (S.empty()) {
            for (auto & word : words)
                if (word.empty())
                    rtn++;
            return rtn;
        }
        
        // 统计S，然后对于每个word进行统计，与S的统计进行比较
        // vector<int> statS(26);
        // for (auto s : S) statS[s-'a']++;
        vector<int> statS(1,1);
        string charS(1,S[0]);// 大意了，还需要记录char
        int cnt = 1;
        S.push_back('$');// 为了完成最后一个char的统计
        for (int i = 1; i < S.size(); ++i) {
            if (S[i-1] != S[i]) {
                charS.push_back(S[i]);// 记录char信息
                statS.back() = cnt;// 更新上一个char的计数，然后存入一个新的计数
                statS.push_back(cnt = 1);
            } else {
                cnt++;
            }
        }
        
        for (auto & word : words) {
            if (word.empty()) continue;// S不为空时，对于空word，直接跳过
            
            int indxS = 0;
            int cnt = 1;
            
            vector<int> statW(1,1);
            bool stretchy = true;
            word.push_back('$');// 为了完成最后一个char的统计
            for (int i = 1; i < word.size(); ++i) {
                if (word[i-1] != word[i]) {
                    // 考不考虑把这一块抽取为一个函数
                    // if (statS[indxS] != cnt && statS[indxS] < 3) {
                    if (word[i-1] == charS[indxS]
                        && (statS[indxS] == cnt || (statS[indxS] >= 3 && statS[indxS] > cnt))) {
                    //if (statS[indxS] == cnt || (statS[indxS] >= 3 && statS[indxS] > cnt)) {
                        indxS++;
                    } else {
                        stretchy = false;
                        break;
                    }
                    statW.back() = cnt;
                    statW.push_back(cnt = 1);
                } else {
                    cnt++;
                }
            }
            //rtn += (stretchy);
            rtn += (stretchy && statW.size() == statS.size());
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<string> words;
    string S;
    rtn = gua.expressiveWords(S="abcd", words={"abc"});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.expressiveWords(S="heeellooo", words={"hello","hi","helo"});
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
