
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    vector<TrieNode*> nodes;
    const string *word;// 这个指针等价于常规TrieNode里面的flag，可以借此表明是否是leaf节点；这里用于指向存在的string
    TrieNode(): nodes(26), word(NULL){};
    // 由于这里的TrieNode里面用的是pointer，所以需要增加专门的析构函数，否则会出现内存泄漏
    ~TrieNode() {
        for (auto node : nodes) delete node;
    }
};

class Solution {
public:
    vector<pair<int,int>> dirs{{-1,0},{0,-1},{1,0},{0,1}};
    int m; int n;

    // 借助Trie的解法
    //Runtime: 388 ms, faster than 45.88%
    //Memory Usage: 9.2 MB, less than 30.43%
    void dfsTrie(vector<vector<char>>& board, TrieNode* node, int x, int y,
                 vector<string> &rtn) {
        // 使用board[x][y]之前要保证index合法性，还要防止重复访问
        if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] == '@')
            return;
        
        char org = board[x][y]; // 直接在原始board上面修改，把board也当作了visit数组
        TrieNode* next = node->nodes[org-'a'];
        if (!next)
            return;
        
        if (next->word) {
            rtn.push_back(*(next->word));
            next->word = NULL; // 这里的小trick可以避免重复word加入rtn，只加入一次
        }
        
        board[x][y] = '@';
        // 然后此时做选择，把邻居来一遍
        for (auto & dir : dirs) {
            int tx = x + dir.first, ty = y + dir.second;
            dfsTrie(board, next, tx, ty, rtn);
        }
        board[x][y] = org;
        return;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode root;//上帝节点
        m = board.size(); n = board[0].size();
        
        vector<string> rtn;
        // 这里必须用const，否则TrieNode里面的word指针赋值会失败吧
        for (string & word: words) {
            TrieNode *prev = &root;
            for (auto c : word) {
                // 这里是指向指针的reference，不好理解的话可以把TrieNode*写成auto
                TrieNode* &next = prev->nodes[c-'a'];
                if (!next)
                    next = new TrieNode();//因为是reference，所以相当于是修改了prev->nodes[c-'a']
                prev = next;
            }
            // 处理完了一个word之后，此时的prev对应的是word[-1]这个char
            prev->word = &word;//这里把word的地址给TrieNode，后续可以不借助path直接定位到word，适用于iterative的情况
        }
        
        // 由于words长度很长，所以本题的思路是遍历board
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dfsTrie(board, &root, i, j, rtn);
            }
        }
        return rtn;
    }
    
    bool dfs(vector<vector<char>>& board, int x, int y,
             string word, int pos, vector<vector<char>>& visit) {
//        if (pos == word.size())
//            return true;//size = word.size();
        if (pos == word.size()-1) {
            return board[x][y] == word[pos];// 对于word有长度的这种情况，需要多加一个判断
        }

        bool isOnboard = false;
        if (board[x][y] != word[pos])
            return isOnboard;
        visit[x][y] = '@';

        // 访问(x,y)的4个邻居，水平和垂直
        for (auto & dir : dirs) {
            int tx = x + dir.first, ty = y + dir.second;
            //if (tx < 0 || tx >= m || ty < 0 || ty >= m || visit[tx][ty] == '@') continue;//大意啦！！
            if (tx < 0 || tx >= m || ty < 0 || ty >= n || visit[tx][ty] == '@') continue;

            if (dfs(board, tx, ty, word, pos+1, visit)) {
                isOnboard = true;
                break;
            }
        }
        visit[x][y] = board[x][y];//恢复回来
        return isOnboard;
    }

    // 这种方法又超时了。。。尼玛
    vector<string> findWords1(vector<vector<char>>& board, vector<string>& words) {
        // 如果不增加一个哈希表确定word的起始位置，那么每次都需要遍历一遍baord
        // 时间复杂度就是len(words) * O(m*n) * len(word)
        m = board.size(); n = board[0].size();
        unordered_map<char, vector<pair<int,int>>> memo;//这个可以减少O(m*n)到O(1)
        for (int i = 0; i < m; ++i) {
          for (int j = 0; j < n; ++j) {
            memo[board[i][j]].push_back({i,j});
          }
        }

        vector<vector<char>> visit = board;
        //vector<string> rtn; 由于可能出现重复，所以使用set
        unordered_set<string> rtn;
        for (auto & word : words) {
            auto iter = memo.find(word[0]);
            if (end(memo) == iter) {
                continue;// 字符不在board上，直接下一个
            }

            for (auto &coord: iter->second) {
                int x = coord.first, y = coord.second;//这里面是每一个(x,y)
                // 此时是上帝视角，还没有处理x和y
                // if (dfs(memo, board, word, 1, visit))
                if (dfs(board, x, y, word, 0, visit))
                    //rtn.push_back(word);
                    rtn.insert(word);
            }
        }

        //return rtn;
        return vector<string>(rtn.begin(), rtn.end());
    }
};

ostream &operator<< (ostream& os, vector<string> &rtn) {
  os << "[";
  for (auto &word : rtn) {
    os << word << ",";
  }
  os << "]";
  return os;
}

int main() {
  Solution gua;
  vector<string> rtn, words;
  vector<vector<char>> board;

  board = {{'a','b'}};
  words = {"ab"};
  rtn = gua.findWords(board, words);
  cout << "expect value = [ab], actual value = " << rtn << endl;

  board = {{'a'}};
  words = {"a"};
  rtn = gua.findWords(board, words);
  cout << "expect value = [a], actual value = " << rtn << endl;
  
  board = {{'o','a','a','n'}, {'e','t','a','e'}, {'i','h','k','r'}, {'i','f','l','v'}};
  words = {"oath","pea","eat","rain"};
  rtn = gua.findWords(board, words);
  cout << "expect value = [eat, oath], actual value = " << rtn << endl;

  board = {{'o','a','b','n'},{'o','t','a','e'},{'a','h','k','r'},{'a','f','l','v'}};
  words = {"oa","oaa"};
  rtn = gua.findWords(board, words);
  cout << "expect value = [oa, oaa], actual value = " << rtn << endl;

  board = {{'a','b'}, {'c','d'}};
  words = {"abcd"};
  rtn = gua.findWords(board, words);
  cout << "expect value = [], actual value = " << rtn << endl;

  return 0;
}
