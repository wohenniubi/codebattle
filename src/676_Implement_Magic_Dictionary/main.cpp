
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class MagicDictionary {
public:
    unordered_map<int, vector<string>> memo;
    
    //Runtime: 20 ms, faster than 99.81%
    //Memory Usage: 18.5 MB, less than 85.82%
    MagicDictionary() {
        // 先想一个可行解，桶排序，然后每个桶里面将新单词与字典的单词进行注意比较
        // 时间复杂度O(n^3), n属于[0,100]
        memo.clear();
    }
    
    void buildDict(vector<string> dictionary) {
        for (auto & word : dictionary) {
            memo[word.size()].push_back(word);
        }
    }
    
    bool search(string searchWord) {
        int size = searchWord.size();
        
        if (memo.count(size) == 0)
            return 0;
        
        for (auto & word : memo[size]) {
            // 单词逐一比较，有且仅有一处不同;
            int cnt = 0;
            for (int i = 0; i < size; ++i) {
                if (word[i] != searchWord[i]) {
                    cnt++;
                    if (cnt > 1) break;
                }
            }
            if (cnt == 1)
                return true;//否则继续for循环
        }
        return false;//如果跳出外部for循环，说明没有找到，那么返回false，没毛病
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

int main(int argc, const char * argv[]) {
    MagicDictionary gua;
    vector<string> dict;
    string word;
    
    gua.buildDict(dict={"hello", "leetcode"});
    cout << "expect value = 0, actual value = " << gua.search(word="hello") << endl;
    cout << "expect value = 1, actual value = " << gua.search(word="hhllo") << endl;
    cout << "expect value = 0, actual value = " << gua.search(word="hell") << endl;
    cout << "expect value = 0, actual value = " << gua.search(word="leetcoder") << endl;

    return 0;
}
