
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 44 ms, faster than 67.41%
    //Memory Usage: 15.6 MB, less than 88.49%
    int maxProduct(vector<string>& words) {
        // 先对单词进行预处理，因为只有26个lowercase，所以一个32bit的数可以搞定
        int size = words.size();
        vector<int> memo(size);
        for (int i = 0; i < size; ++i) {
            int tmp = 0;
            for (auto c : words[i]) {
                tmp |= 1<<(c-'a');
            }
            memo[i] = tmp;
        }
        
        // 两重循环判断最大乘积
        int rtn = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = i+1; j < size; ++j) {
                if (memo[i] & memo[j])
                    continue;// 说明有相同的字母
                int plen = words[i].size() * words[j].size();
                // rtn = max(rtn, words[i].size() * words[j].size()); 还不能这么做，因为size()的类型是unsigned int，max要求两个type一致
                rtn = max(rtn, plen);
            }
        }
        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    vector<string> words;
    rtn = gua.maxProduct(words = {"a","aa","aaa","aaaa"});
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.maxProduct(words = {"a","ab","abc","d","cd","bcd","abcd"});
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.maxProduct(words = {"abcw","baz","foo","bar","xtfn","abcdef"});
    cout << "expect value = 16, actual value = " << rtn << endl;
    return 0;
}
