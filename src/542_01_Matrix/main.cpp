
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    //Runtime: 68 ms, faster than 70.19%
    //Memory Usage: 28.7 MB, less than 69.20%
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        vector<pair<int,int>> dirs{{1,0},{0,1},{-1,0},{0,-1}}; // 下右上左
        // 感觉这不就是简单的图遍历吗？可以把visit数组作为历史信息，直接利用
        // 然后由于要得到最近的0，所以用BFS；不过问题的关键是，如果以每一个0作为起点，必定是超时；
        // 需要跳过一些0的点，例如与0紧挨的0 —— 这里巧妙的利用了visit数组，让其值变得多样一些
        int row = mat.size(), col = mat[0].size();
        //if (!row) return {};
        
        vector<vector<int>> visit = mat;
        queue<pair<int,int>> candi;
        
        // 先搜集所有等于0的点，同时把等于1点的值改一改，这样可以配合之后以0作为root的BFS
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (visit[i][j] == 0) {
                    candi.push({i,j});
                } else {
                    visit[i][j] = INT_MAX;
                }
            }
        }
        
        // 现在开始以0作为root开始BFS遍历
        while (candi.size()) {
            int size = candi.size();
            // 层序遍历是常规操作
            for (int i = 0; i < size; ++i) {
                auto [x, y] = candi.front();
                candi.pop();
                
                for (auto & dir: dirs) {
                    int tx = x + dir.first, ty = y + dir.second;
                    
                    // 如果visit[x][y]+1 > visit[tx][ty]，那么会重复加入
                    if (tx < 0 || tx >= row || ty < 0 || ty >= col || visit[x][y]+1 >= visit[tx][ty])
                        continue;
                    
                    candi.push({tx, ty});
                    visit[tx][ty] = visit[x][y]+1;// 对应于修改vist点flag
                }
            }
        }
        return visit;// 都不用创建return数组了，有了以上操作，visit就是所求
    }
};

ostream & operator<<(ostream &os, vector<vector<int>> &rtn) {
    os << "[";
    for (auto &row : rtn) {
        os << "[";
        for (auto val : row) os << val << ", ";
        os << "]" << endl;
    }
    
    os << "]" << endl;
    return os;
}

int main(int argc, const char * argv[]) {
    Solution gua;
    
    vector<vector<int>> rtn, mat;
    rtn = gua.updateMatrix(mat = {{0,0,0}, {0,1,0}, {0,0,0}});
    cout << rtn;
    return 0;
}
