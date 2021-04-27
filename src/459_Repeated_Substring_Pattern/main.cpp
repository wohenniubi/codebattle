
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Solution {
public:
    //Runtime: 348 ms, faster than 9.60%
    //Memory Usage: 154.2 MB, less than 13.77%
    void getKmp(vector<vector<int>> &memo, string &s) {
        int size = s.size();
        memo[0][s[0]-'a'] = 1;
        
        int prev = 0;
        for (int i = 1; i < size; ++i) {
            int pos = s[i]-'a';
            for (int j = 0; j < 26; ++j) {
                memo[i][j] = memo[prev][j];
            }
            memo[i][pos] = i+1;
            prev = memo[prev][pos];
        }
        return;
    }
    
    bool repeatedSubstringPattern(string s) {
        // 这里不要纠结这个问题了，就记住这个trick，先翻倍得到s+s，然后去掉头尾得到s'，如果s仍然包含在s'里面，说明可以被重复
        int size = s.size();
        //string ns = s.substr(1).insert(s.begin(), prev(s.end()));// s+s，再去掉头尾
        string ns = s.substr(1);
        ns.insert(ns.end(), s.begin(), prev(s.end()));
        
        // 然后基于s计算KMP数组
        unique_ptr<vector<vector<int>>> memo(new vector<vector<int>>(size, vector<int>(26)));
        getKmp(*memo, s);
        
        bool rtn = false;
        int n = 0;
        for (int i = 0; i < ns.size(); ++i) {
            int pos = ns[i]-'a';
            n = (*memo)[n][pos];
            if (n == s.size()) {
                rtn = true;
                break;
            }
        }
        
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    bool rtn;
    string s;
    
    rtn = gua.repeatedSubstringPattern(s="abab");
    cout << "expect value = 1, actual value = " << rtn << endl;

    rtn = gua.repeatedSubstringPattern(s="aba");
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.repeatedSubstringPattern(s="abcabcabcabc");
    cout << "expect value = 1, actual value = " << rtn << endl;
    return 0;
}
