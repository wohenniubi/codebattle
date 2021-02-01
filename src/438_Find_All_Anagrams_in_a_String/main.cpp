
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // 看到这种题，很可能就是滑动窗，就是567那道题的翻版,anagram就是permutation
        unordered_map<char,int> mapS, mapP;
        for (auto x : p) mapP[x]++;
        
        vector<int> rtn;
        int lhs = 0, valid = 0;
        
        for (int i = 0; i < s.size(); ++i) {
            char x = s[i];
            mapS[x]++;
            if (mapP.count(x)) {
                if (mapP[x] == mapS[x])
                    valid++;// x这个字符满足条件了
            }
            
            // 这个相当于滑动窗长是固定的，所以if就可以了
            if (i-lhs+1 == p.size()) {
                if (valid == mapP.size())
                    rtn.push_back(lhs);
                
                // 需要去掉最左边的char
                char tmp = s[lhs];
                if (mapP.count(tmp))
                    if (mapP[tmp] == mapS[tmp])
                        valid--;
                
                mapS[tmp]--;
                lhs++;
            }
        }
        return rtn;
    }
};

ostream & operator<< (ostream &os, vector<int> &rtn) {
    os << "[";
    for (auto val : rtn) os << val << ", ";
    os << "]" << endl;
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    string s1, s2;
    vector<int> rtn;

    rtn = gua.findAnagrams(s1="cbaebabacd", s2="abc");
    cout << "expect value = [0, 6], actual value = " << rtn << endl;
    
    rtn = gua.findAnagrams(s1="abab", s2="ab");
    cout << "expect value = [0, 1, 2], actual value = " << rtn << endl;
    return 0;
}

