
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    unordered_map<string, int> memo;// 记录similarities的词编号
    
    //Runtime: 156 ms, faster than 97.46%
    //Memory Usage: 54.4 MB, less than 96.74%
    class UnionFound {
        vector<int> parents;
    public:
        UnionFound(int size) {
            parents.resize(size);
            for (int i = 0; i < size; ++i) parents[i] = i;
        }
        // 找到parent
        int find(int id) {
            if (id < 0 || id >= parents.size()) return -1;// 输入保护
            while (parents[id] != id) {
                parents[id] = parents[parents[id]];
                id = parents[id];
            }
            return id;
        }
        void unit(int idA, int idB) {
            int parentA = find(idA);
            int parentB = find(idB);
            if (parentA != parentB) {
                parents[parentA] = parentB;
            }
        }
    };
    
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) return false;
        
        // 一看到这个similarities，以及它的传递性，就想到Union found
        // 稍微不一样的地方是，这里是每个word，之前的Union found都是一个数，那就映射一下吧
        for (auto & wordPair : similarPairs) {
            // auto & [word1, word2] = wordPair; // wordPair是个vector，还不能decompose为tuple
            auto & word1 = wordPair[0], & word2 = wordPair[1];
            if (!memo.count(word1)) memo[word1] = memo.size();
            if (!memo.count(word2)) memo[word2] = memo.size();
        }
        
        // 要在for循环结束，收集齐了所有的数字，然后再进行Union found
        UnionFound helper(memo.size());
        for (auto & wordPair : similarPairs) {
            // auto & [word1, word2] = wordPair; // wordPair是个vector，还不能decompose为tuple
            auto & word1 = wordPair[0], & word2 = wordPair[1];
            helper.unit(memo[word1], memo[word2]);
        }
        
        for (int i = 0; i < sentence1.size(); ++i) {
            auto & word1 = sentence1[i];
            auto & word2 = sentence2[i];
            if (word1 == word2) continue;// 别大意，相同的word不需要比较

            int id1 = -1, id2 = -1;
            if (!memo.count(word1))
                return false;
            else
                id1 = memo[word1];
            if (!memo.count(word2))
                return false;
            else
                id2 = memo[word2];
            
            if (helper.find(id1) != helper.find(id2))
                return false;
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    vector<string> sentence1, sentence2;
    vector<vector<string>> similarPairs;
    
    bool rtn;
    rtn = gua.areSentencesSimilarTwo(sentence1={"great","acting","skills"},
                                     sentence2={"fine","drama","talent"},
                                     similarPairs = {{"great","good"},{"fine","good"},
                                                    {"drama","acting"},{"skills","talent"}});
    cout << "expect value = 1, actual value = " << rtn << endl;
    rtn = gua.areSentencesSimilarTwo(sentence1={"I","love","leetcode"},
                                     sentence2={"I","love","onepiece"},
                                     similarPairs = {{"manga","onepiece"},{"platform","anime"},
                                                    {"leetcode","platform"},{"anime","manga"}});
    cout << "expect value = 1, actual value = " << rtn << endl;
    rtn = gua.areSentencesSimilarTwo(sentence1={"I","love","leetcode"},
                                     sentence2={"I","love","onepiece"},
                                     similarPairs = {{"manga","hunterXhunter"},{"platform","anime"},
                                                    {"leetcode","platform"},{"anime","manga"}});
    cout << "expect value = 0, actual value = " << rtn << endl;

    return 0;
}
