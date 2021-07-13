#include <iostream>
#include <vector>

using namespace std;

class Trie {
public:
    // Runtime: 60 ms, faster than 62.96%
    // Memory Usage: 45.7 MB, less than 30.60%
    /** Initialize your data structure here. */
    Trie() {
        ;
    }
    ~Trie() {
        isWord = false;
        for (int i = 0; i < 26; ++i)
            delete kids[i];
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* next = this;
        for (auto c : word) {
            auto & tmp = next->kids[c - 'a'];
            
            if (!tmp) {
                tmp = new Trie();
            }
            next = tmp;
        }
        next->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *next = this;
        for (auto c : word) {
            if (NULL == next->kids[c - 'a']) return false;
            next = next->kids[c - 'a'];
        }
        return next->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *next = this;
        for (auto c : prefix) {
            if (NULL == next->kids[c - 'a']) return false;
            next = next->kids[c - 'a'];
        }
        return true;
    }
    
    Trie* kids[26] = {};
    bool isWord = false;
};

class Trie1 {
public:
		// 可以使用this指针，这样就不用创建TrieNode *root节点了, e.g. Trie next = this;
    class TrieNode {
        vector<TrieNode*> kids;
        bool isWord;
    public:
        TrieNode() {
            kids.resize(26);
            isWord = false;
        }
        ~TrieNode() {
            isWord = false;
            for (auto kid : kids) 
                if (kid)
                    delete kid;
        }
    friend Trie1;
    };
    
    /** Initialize your data structure here. */
    Trie1() {
        root = new TrieNode();
    }
    ~Trie1() {
        if (root) delete root;
        root = NULL;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* next = root;
        for (auto c : word) {
            auto & tmp = next->kids[c - 'a'];
            
            if (!tmp) {
                tmp = new TrieNode();
            }
            next = tmp;
        }
        next->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *next = root;
        for (auto c : word) {
            if (NULL == next->kids[c - 'a']) return false;
            next = next->kids[c - 'a'];
        }
        return next->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *next = root;
        for (auto c : prefix) {
            if (NULL == next->kids[c - 'a']) return false;
            next = next->kids[c - 'a'];
        }
        return true;
    }
    
    TrieNode* root;
};

int main() {
  Trie gua;
  string word, prefix;
  bool rtn;

  gua.insert(word = "apple");
  cout << "expect result = 1, actual result = " << gua.search(word="apple") << endl;
  cout << "expect result = 0, actual result = " << gua.search(word="app") << endl;
  cout << "expect result = 1, actual result = " << gua.startsWith(prefix="app") << endl;
  gua.insert(word = "app");
  cout << "expect result = 1, actual result = " << gua.search(word="app") << endl;
  return 0;
}

