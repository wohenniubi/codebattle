
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 12 ms, faster than 78.53%
    //Memory Usage: 8.7 MB, less than 53.51%
    string removeDuplicates(string s, int k) {
        //我想的办法就是使用一个stack来存index，先获得删除之后的array
        vector<pair<char,int>> st(1,{'*',0});
        //vector<int> st; 仅有index不能完成删除功能

        for (int i = 0; i < s.size(); ++i) {
            // 这里的auto实际上是tie(preChar, cnt)
            auto & [preChar, cnt] = st.back();
            if (preChar != s[i]) {
                st.push_back({s[i], 1});
            } else {
                cnt++;
                if (cnt == k) {
                    st.pop_back();
                }
            }
        }
        // 现在开始构造需要返回的string
        string rtn;
        for (auto & [preChar, cnt] : st) {
            rtn.append(cnt, preChar);
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn, s;
    int k;
    
    rtn = gua.removeDuplicates(s = "abcd", k=2);
    cout << "expect result = abcd, actual result = " << rtn << endl;

    rtn = gua.removeDuplicates(s = "deeedbbcccbdaa", k=3);
    cout << "expect result = aa, actual result = " << rtn << endl;

    rtn = gua.removeDuplicates(s = "pbbcggttciiippooaais", k=2);
    cout << "expect result = ps, actual result = " << rtn << endl;
    return 0;
}

