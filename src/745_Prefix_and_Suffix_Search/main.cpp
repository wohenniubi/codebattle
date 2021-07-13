
#include <iostream>
#include <vector>

using namespace std;

class WordFilter {
public:
    //Runtime: 396 ms, faster than 81.16%
    //Memory Usage: 189.7 MB, less than 34.78%
    class Trie {
    public:
        ~Trie() {
            isWord = false;
            for (int i = 0; i < 27; ++i)
                delete kids[i];
        }
        
        //Trie* insert(string &word) {
        Trie* insert(string &word, int idx) { // 需要把这一路上的index都修改为indx
            Trie* next = this;
            for (auto c : word) {
                auto &tmp = next->kids[c-'a'];
                if (!tmp)
                    tmp = new Trie();
                next = tmp;
                next->idx = idx;
            }
            next->isWord = true;// 跳出for循环时next必定是最后的叶子节点
            return next;// 原本不需要有返回值Trie*
        }
        
        Trie* startswith(string &prefix) {
            Trie *next = this;
            for (auto c : prefix) {
                auto tmp = next->kids[c-'a'];
                if (!tmp) return NULL;//false
                next = tmp;
            }
            return next;//true;
        }
        
        Trie* kids[27] = {};// 这里用到个小技巧，使用'{'，它刚好是z的后一位，这样可以连续
        bool isWord = false;
        int idx = -1;// 使用suffix + prefix这种方式时可能出现重复，此时题目要求返回较大的（靠后）的词，因此要保存这个值
    };
    
    WordFilter(vector<string>& words) {
        int cnt = 0;
        
        // 第二个小技巧，把每个word存储为后缀+完整单词的情况，这样可以减少时间和空间复杂度的维度
        for (auto & word : words) {
            // apple被保存为
            // {apple
            // e{apple
            // le{apple
            // ple{apple
            // pple{apple
            // apple{apple
            string tmp = '{' + word;
            for (int i = 0; i <= word.size(); ++i) {
                string sufprefix = word.substr(word.size()-i,i) + tmp;
                //Trie *node = root.insert(sufprefix);
                Trie *node = root.insert(sufprefix, cnt);// 注意要全部替换这个值
                //node->idx = cnt;// 这些前后缀都代表一个word，可能出现重复的sufprefix，此时就会被更新为较大cnt
            }
            cnt++;// 这个word结束之后才更新index
        }
    }
    
    int f(string prefix, string suffix) {
        string tmp = suffix;
        //reverse(begin(tmp), end(tmp));
        string sufprefix = tmp + '{' + prefix;
        Trie *node = root.startswith(sufprefix);
        
        return (!node)? -1 : node->idx;
    }
    Trie root;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<string> words;
    string prefix, suffix;
    
    cout << "\nTest2" << endl;
    WordFilter gua2(words = {"cabaabaaaa","ccbcababac","bacaabccba","bcbbcbacaa","abcaccbcaa","accabaccaa","cabcbbbcca","ababccabcb","caccbbcbab","bccbacbcba"});
    cout << "expect value = 9, actual value = " << gua2.f("bccbacbcba","a") << endl;
    cout << "expect value = 4, actual value = " << gua2.f("ab","abcaccbcaa") << endl;
    cout << "expect value = 5, actual value = " << gua2.f("a","aa") << endl;
    cout << "expect value = 0, actual value = " << gua2.f("cabaaba","abaaaa") << endl;
    cout << "expect value = 8, actual value = " << gua2.f("cacc","accbbcbab") << endl;
    cout << "expect value = 1, actual value = " << gua2.f("ccbcab","bac") << endl;
    cout << "expect value = 2, actual value = " << gua2.f("bac","cba") << endl;
    cout << "expect value = 5, actual value = " << gua2.f("ac","accabaccaa") << endl;
    cout << "expect value = 3, actual value = " << gua2.f("bcbb","aa") << endl;
    cout << "expect value = 1, actual value = " << gua2.f("ccbca","cbcababac") << endl;
    
    cout << "\nTest1" << endl;
    WordFilter gua(words = {"apple"});
    cout << "expect value = 0, actual value = " << gua.f(prefix="a", suffix="e") << endl;
    cout << "expect value = -1, actual value = " << gua.f(prefix="e", suffix="a") << endl;
    
    return 0;
}
