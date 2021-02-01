
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 268 ms, faster than 22.19%
    //Memory Usage: 16.5 MB, less than 16.75%
    // 网上的另一种做法，简化了isContained的复杂度O(1)
    string minWindow(string s, string t) {
//        vector<int> mapS(64);
//        vector<int> mapT(64);
        unordered_map<int,int> mapS;
        unordered_map<int,int> mapT;
        
        for (auto x : t) mapT[x-'A']++;
        int valid = 0, len = INT_MAX;
        string rtn;
        
        int lhs = 0;
        for (int i = 0; i < s.size(); ++i) {
            int pos = s[i] - 'A';
            mapS[pos]++;
            //if (mapT[pos] > 0) { 大意了大意了，又忘记mapT[pos]会添加一个数。。。
            if (mapT.count(pos)) {
                // 这里主要用于维护全字符valid计数，让valid仅在单个字符达到门限时加1
                // 然后当valid等于t.size()时认为窗符合条件，此时开始缩短窗左半节点
                if (mapS[pos] == mapT[pos])
                    valid++; // valid是N种字符的合法情况
            }
            
            // 这里原本是if，但是由于窗长不定，所以称为了while
            while (valid == mapT.size()) {
                int posOld = s[lhs]-'A';
                
                // 更新返回string
                if (rtn.empty() || rtn.size() > i-lhs+1) {
                    rtn = s.substr(lhs, i-lhs+1);
                }
                // 去掉某个char之前对于valid的维护
                // if (mapT[posOld] > 0) { 不要大意啊不要大意啊，maoT[posOld]会直接添加的哟
                if (mapT.count(posOld)) {
                    if (mapS[posOld] == mapT[posOld])
                        valid--;
                }
                mapS[posOld]--;
                lhs++;
            }
        }
        return rtn;
    }

    class charCnt {
    public:
        // int total;
        vector<int> dict;
        
        charCnt(string & t) {
            // total = 0;
            dict.resize(128,0); // 足够cover大小字母了
            for (char x : t) addChar(x);
        }
        void addChar(char x) {
            //dict[x-'a']++; //大意了大意了，'A'比‘a’小，越界了！！！
            dict[x-'A']++;
            // total++;
        }
        void delChar(char x) {
            //dict[x-'a']--; //大意了大意了，'A'比‘a’小，越界了！！！
            dict[x-'A']--;
            // total++;
        }
        bool isContained(charCnt & base) {
            bool rtn = true;
            for (int i = 0; i < 128; ++i) {
                //if (dict[i] < base.dict[i]) { // 大意了，还要比较base里面的合法位置
                if (dict[i] < base.dict[i]) {
                    rtn = false;
                    break;
                }
            }
            return rtn;
        }
    };
    // 时间复杂度O(128n)
    //Runtime: 268 ms, faster than 6.23%
    //Memory Usage: 16.5 MB, less than 18.04%
    string minWindow1(string s, string t) {
        //来自己试着做一下
        charCnt base(t);
        // charCnt cost(""); 大意了，入参是reference的话，不能传入const类型
        string gua;
        charCnt cost(gua);
        int lhs = 0;
        string rtn;
        for (int rhs = 0; rhs < s.size(); ++rhs) {
            cost.addChar(s[rhs]);
            
            // 缩短滑动窗的左索引，由于滑动窗长不定，所以要用while
            while (cost.isContained(base)) {
                int len = rhs-lhs+1;
                if (rtn.empty() || rtn.size() > len) { // 题目说只有unique解，所以>和>=一样
                    rtn = s.substr(lhs, len);
                }
                // rtn = min(rtn, rhs-lhs+1);
                cost.delChar(s[lhs]);
                lhs++;//大意啦大意啦，别忘记移动左索引
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string s, t, rtn;

    rtn = gua.minWindow(s="a", t = "a");
    cout << "expect result = a, actual result = " << rtn << endl;

    rtn = gua.minWindow(s="ADOBECODEBANC", t = "ABC");
    cout << "expect result = BANC, actual result = " << rtn << endl;

    return 0;
}

