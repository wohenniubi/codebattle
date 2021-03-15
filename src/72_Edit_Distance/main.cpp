
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 一看是字符串的题, 猜测应该用dp, 但是又搞不定递推关系. 
    // 又觉得像是DFS, 有3种option, 但是不知道怎么做; 看的答案
    // 方法1: DFS加上memorize, 因为谁也不知道一步之后对剩余部分有什么影响
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> memo(m, vector<int>(n));
        return helper(word1, 0, word2, 0, memo);
    }

    // helper的含义是从i~size1和j~size2这两个substring的edit距离
    int helper(string &word1, int i, string & word2, int j,
        vector<vector<int>> &memo) {
        // 如果字符串到头了, 那改变的距离就是另一个string的长度
        // if (i == word1.size()) return (word2.size());
        // if (j == word2.size()) return (word1.size());
        // 不要大意啊不要大意啊!! 是另一个string剩余的长度, 
        // 我觉得-i, -j或许是一样, 因为i,j此刻应该相等 
        // if (i == word1.size()) return (word2.size()-i);
        // if (j == word2.size()) return (word1.size()-j);
        // --- 不对, 因为没有到达末尾的那个index长度是不定的, 
        // 正确的应该是某个string就减去这个string当前的index
        if (i == word1.size()) return (word2.size()-j);
        if (j == word2.size()) return (word1.size()-i);

        // 这个memo的意义是为了减少重复计算, 他的含义是什么?
        // 表示word1从0~i和word2从0~j这两个substring的edit距离? 不是哈!!
        // memo表示的也是从i~size1和从j到size2这两个substring的edit距离, 这与helper的定义一致
        // 另外memo是从右往左更新的, 这可以想象出来: 迭代到最深时是word1和word2的最右侧
        if (memo[i][j] > 0) return memo[i][j];
        // 这里memo要不要初始化为INT_MIN, 然后这里判断不等于INT_MIN时就返回,
        // 否则对于右侧很多相同char的word1, word2, 这里都会重复调用一下...
        
        int res = 0;
        // 现在开始对word1[i]和word2[j]进行比较,  
        if (word1[i] == word2[j]) {
            // 如果相等, 只需要比较i+1~word1和j+1~word2这两个substring的edit距离
            res = helper(word1, i+1, word2, j+1, memo);// 不需要+1
        } else {
            // 如果不相等, 三种动作;
            // (1) 将当前i和j修改为相等, 需要1步, 再对i+1~word1和j+1~word2进行比较
            // (2) 去掉word1[i], 需要1步, 然后比较i+1~word1和j~word2进行比较
            // (3) 去掉word2[j], 需要1步, 然后比较i~word1和j+1~word2进行比较
            // 然后需要找到最小的步数, 因为3种动作都加上常数1, 那么只对helper取min
            int replaceCnt = helper(word1, i+1, word2, j+1, memo);
            int deleteCnt = helper(word1, i+1, word2, j, memo);
            int insertCnt = helper(word1, i, word2, j+1, memo);
            res = 1 + min(insertCnt, min(replaceCnt, deleteCnt));
        }
        // 最后千万不要忘记更新memo数组啊
        return memo[i][j] = res;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    int rtn;
    string word1, word2;
    
    rtn = gua.minDistance(word1 = "me", word2 = "me");
    cout << "expect value = 0, actual value = " << rtn << endl;

    rtn = gua.minDistance(word1 = "horse", word2 = "ros");
    cout << "expect value = 3, actual value = " << rtn << endl;

    rtn = gua.minDistance(word1 = "intention", word2 = "execution");
    cout << "expect value = 5, actual value = " << rtn << endl;

    return 0;
}

