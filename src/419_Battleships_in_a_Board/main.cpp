#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int,int>> dirs{{0,1},{-1,0},{0,-1},{1,0}};

    void dfs(vector<vector<char>> &board, int x, int y) {
        // 返回条件TODO
        // 没有使用visit数组，直接在board上面修改
        board[x][y] = 'O';
        for (auto &dir : dirs) {
            int tx = x+dir.first, ty = y +dir.second;
            if (tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size() || board[tx][ty] != 'X')
                continue;
            dfs(board, tx, ty);
        }

        return;
    }

    int countBattleships(vector<vector<char>>& board) {
        // 貌似就是最简单的 BFS + DFS
        int rtn = 0;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 'X') {
                    dfs(board, i, j);
                    ++rtn;
                }
            }
        }

        return rtn;
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<char>> board;
    int rtn;
    rtn = gua.countBattleships(board={{'X','.','.','X'},{'.','.','.','X'},{'.','.',',','X'}});
    cout << "expect value = 2, actual value = " << rtn << endl;
    return 0;
}


