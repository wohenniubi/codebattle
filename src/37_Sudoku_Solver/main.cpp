
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> rows;
    vector<vector<int>> cols;
    vector<vector<int>> ties;
    //vector<vector<char>> solution;
    
    #define C2INDEX(x)  (x-'1')
    #define INDEX2C(x)  (x+'1')
    
    void setPos(int x, int y, int pos, int val = 0) {
        int x3 = x/3, y3 = y/3;
        ties[pos][3*y3+ x3] = val;
        rows[pos][x] = val;
        cols[pos][y] = val;
    }
    
    bool isValid(int x, int y, int pos) {
        int x3 = x/3, y3 = y/3;
        return (0 == ties[pos][3*y3+ x3])
            && (0 == rows[pos][x]) && (0 == cols[pos][y]);
    }
    
    //Runtime: 8 ms, faster than 89.29%
    //Memory Usage: 6.6 MB, less than 55.51%
    void solveSudoku(vector<vector<char>>& board) {
        // 回溯法解决，首先创建一些memo
        rows.resize(9, vector<int>(9));
        cols.resize(9, vector<int>(9));
        ties.resize(9, vector<int>(9));
        //solution = board;
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                char c = board[x][y];
                //if (isdigit(c)) setPos(x, y, c-'0', 1);// 大意了，数独没有'0'
                if (isdigit(c)) setPos(x, y, C2INDEX(c), 1);
            }
        }
        
        // 这里首先是采用递归的方式遍历一个2D数组，然后再对每个位置进行决策判断，每一个决策值还要继续前面的递归
        // 因此这个递归遍历固定从x,y这个位置开始向右向下遍历，当达到最右之后向下一行操作
        int M = 9, N = 9;
        function<bool(vector<vector<char>>&, int, int)> traverse = [&](vector<vector<char>> &board, int x, int y) -> bool {
            
            // 返回条件TODO: 首先是y越界之后的操作，然后是x到达最后一行的操作
            if (y == N) return traverse(board, x+1, 0);
            if (x == M)
                return true;
            
            for (int i = x; i < M; ++i) {
                for (int j = y; j < N; ++j) {
                    // 然后对每一个位置的决策进行选择，借助memo数组，可以很快跳过check，无需遍历
                    char c = board[i][j];
                    
                    // isValid()的处理，之前已经设置过了
                    // if (isdigit(c)) continue; 注意这里如果continue，会继续执行for loop，导致重复计算
                    // 递归调用traverse的话就可以让调用次数由for loop变为1
                    if (isdigit(c)) {
                        return traverse(board, i, j+1);
                    }
                    
                    // 决策有9种
                    for (int d = 0; d < N; ++d) {
                        // if (!isValid(i, j, c-'0')) continue; 大意啦，数独没有'0'
                        if (!isValid(i, j, d)) continue;
                        
                        // push操作
                        // setPos(i, j, c-'0', 1); 大意啦，数独没有'0'
                        setPos(i, j, d, 1);
                        board[i][j] = INDEX2C(d);// 又大意啦，忘记在solution里面加入操作了

                        if (traverse(board, i, j+1)) return true;
                        
                        // pop操作
                        // setPos(i, j, c-'0', 0); 大意啦，数独没有'0'
                        setPos(i, j, d, 0);
                        board[i][j] = '.';
                    }
                    
                    // 惊天大秘密，这里需要进行判断，如果for循环结束都还没有返回true，说明这一行没有可行解
                    return false;
                }
            }
            return false;// 因为必然有解，所以这里应该不会跳出循环，跳出说明在当前情况下无解，需要回退
        };
        
        traverse(board, 0, 0);
        return;
    }
};

ostream & operator<< (ostream &os, vector<vector<char>> &board) {
    os << "[\n";
    for (auto & rows : board) {
        os << "[";
        for (auto & col : rows) os << col << "  ";
        os << "]" << endl;
    }
    
    os << "]";
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    vector<vector<char>> board;
    board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};

    cout << "before solving the problem, the board is\n" << board << endl;
    gua.solveSudoku(board);
    cout << "after  solving the problem, the board is\n" << board << endl;

    return 0;
}

